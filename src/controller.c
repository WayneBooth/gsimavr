
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include <avr_ioport.h>

#include "logger.h"
#include "ac_input.h"
#include "view.h"
#include "model.h"
#include "controller.h"

ac_input_t ac_input;

char *ports = "";

void watcher_state_in(struct avr_irq_t* irq, uint32_t value, void* closure ) {
  UNUSED(irq);

  char p = (char)*(char *)closure;
  int state = 0;

  if( value >= 10 ) {
    state = 1;
    value -= 10;
  }
   
  LOG( LOGGER_DEBUG, "In pin change: port%c%d = %d\n", p, value, state);

  set_ioState( 
	reg_pin_to_location( p, value ), 
	state 
	);

  renderScene();
}

void watcher_ddr(struct avr_irq_t* irq, uint32_t value, void* closure) {
  UNUSED(irq);

  int x = 0;
  char p = (char)*(char *)closure;
  LOG( LOGGER_DEBUG, "Entering 'watcher_ddr', port%c = %d\n", p, value);

  for ( x = 0; x < 8 ; x++ ) {
    set_ddr( 
	reg_pin_to_location( p, x ), 
	( value & ( 1 << x ) ) >= 1 
	);
    LOG( LOGGER_DEBUG, "PIN%c%d = ddr is %d\n", p, x, ( value & ( 1 << x ) ) >= 1 );
    if( ( value & ( 1 << x ) ) == 0 ) {
      avr_irq_register_notify(
                avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( p ), x ),
                watcher_state_in, closure );
    }

  }
  renderScene();
}

void watcher_state_out(struct avr_irq_t* irq, uint32_t value, void* closure) {
  UNUSED(irq);

  int x = 0;
  char p = (char)*(char *)closure;
  LOG( LOGGER_DEBUG, "Out pin change: port%c = %d\n", p, value);

  for ( x = 0; x < 8 ; x++ ) {
    set_ioState( 
	reg_pin_to_location( p, x ), 
	( value & ( 1 << x ) ) >= 1 
	);
	LOG( LOGGER_TRACE, "PIN%c%d = %d\n", p, x, ( value & ( 1 << x ) ) >= 1 );
  }
  renderScene();
}

int changeInput( int pin, int newState ) {

	int element = -1;

	int p = 0;
	int l = strlen(ports);
	if( l == 0 ) {
		LOG( LOGGER_ERROR, "No device registers have been set.\n" );
		return 1;
	}

	for( p = 0 ; p < l ; p++ ) {
		int e = 0;
		for( e = 0 ; e < 8 ; e++ ) {
			if( reg_pin_to_location( ports[p], e ) == pin ) {
				element = e;
				LOG( LOGGER_DEBUG, "You clicked port%c%d\n", ports[p], element);
				goto end;
			}
		}
	}

end:
	if( element == -1 ) {
		LOG( LOGGER_ERROR, "Could not find the register/pin for pysical pin no: %d\n", pin );
		return 1;
	}

	LOG( LOGGER_DEBUG, "state = %d\n", newState );

//	avr_unconnect_irq(
//        	ac_input.irq + IRQ_AC_OUT,
//		avr_io_getirq(
//        	        	avr,
//                		AVR_IOCTL_IOPORT_GETIRQ(ports[p]),
//	                element)
//		);

	if( newState == BUTTON_ON ) {
		LOG( LOGGER_TRACE, "Raising IRQ on physical pin %d = port%c%d, to ON\n", pin, ports[p], element );
	        avr_raise_irq(
        	        avr_io_getirq(
                	        avr, 
	                        AVR_IOCTL_IOPORT_GETIRQ(ports[p]), 
         	                element ),
                	10 + element );
	}

	else if( newState == BUTTON_OFF ) {
		LOG( LOGGER_TRACE, "Raising IRQ on physical pin %d = port%c%d, to OFF\n", pin, ports[p], element );
	        avr_raise_irq(
        	        avr_io_getirq(
                	        avr, 
	                        AVR_IOCTL_IOPORT_GETIRQ(ports[p]), 
         	                element ),
                	element );
	}

	else if( newState == BUTTON_AC ) {
		LOG( LOGGER_TRACE, "Pin %d AC\n", pin );
		avr_connect_irq(
        		ac_input.irq + IRQ_AC_OUT,
		        avr_io_getirq(
        	        	   avr,
                		   AVR_IOCTL_IOPORT_GETIRQ(ports[p]),
		                   element)
	        	);
	}

	return 0;
}


void * avr_run_thread( void * ignore ) {
	UNUSED(ignore);
	int state = cpu_Running;
	while ( ( state != cpu_Done ) && ( state != cpu_Crashed ) ) {
		state = avr_run ( avr );
        }
	pthread_detach(pthread_self());
        return NULL;
}

int setupConnectivity() {

  if( REGISTERS == NULL ) {
    LOG( LOGGER_ERROR, "Looks like we've not loaded a core yet\n" );
    return 1;
  }
  ports = REGISTERS();
  if( ports == NULL ) {
    LOG( LOGGER_ERROR, "No record of which registers\n" );
    return 1;
  }

  int p = 0;
  int l = strlen(ports);
  for( p = 0 ; p < l ; p++ ) {

    LOG( LOGGER_ERROR, "Registering the avr registers '%c'\n", ports[p] );

    // Check for DDR changes
    avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( ports[p] ), IOPORT_IRQ_DIRECTION_ALL ),
		watcher_ddr, &(ports[p]) );



    // Check for State changes on (output)
    avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( ports[p] ), IOPORT_IRQ_REG_PORT ),
		watcher_state_out, &(ports[p]) );

    // Inputs are set in 'watcher_ddr' when the pin is set as an input

  }


  // Setup Clock
  ac_input_init(avr, &ac_input);

  pthread_t run;
  pthread_create(&run, NULL, avr_run_thread, NULL);

  return 0;
}

