
#include <stdio.h>
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

enum {
	BUTTON_ON = 0,
	BUTTON_AC,
	BUTTON_OFF
};

void watcher_state(struct avr_irq_t* irq, uint32_t value, void* closure) {
  int x = 0;
  for ( x = 0; x < 8 ; x++ ) {
    set_ioState( 
	reg_pin_to_location( 
			(char *)closure, 
			x 
			), 
	( value & ( 1 << x ) ) >= 1 
	);
	//printf("PIN%s%d = %d\n", (char *)closure, x, ( value & ( 1 << x ) ) >= 1 );
  }
  renderScene();
}

void changeInput( int pin, int newState ) {

	char port[2];
	int element;
	port[1] = '\0';

	char *ports = REGISTERS();
	int p = 0;
	for( p = 0 ; p < strlen(ports) ; p++ ) {
		memcpy( port, &ports[p], 1);
		int e = 0;
		for( e = 0 ; e < 8 ; e++ ) {
			element = e;
			if( reg_pin_to_location( port, element ) == pin ) {
				LOG( LOGGER_DEBUG, "You clicked %s%d\n", port, element);
				goto end;
			}
		}
	}

end:

	LOG( LOGGER_DEBUG, "state = %d\n", newState );
//	avr_unconnect_irq(
//        	ac_input.irq + IRQ_AC_OUT,
//		avr_io_getirq(
//        	        	avr,
//                		AVR_IOCTL_IOPORT_GETIRQ(port[0]),
//		                element)
//		);

	if( newState == BUTTON_ON ) {
		LOG( LOGGER_WARNING, "Pin %d Port %c%d ON\n", pin, port[0], element );
	        avr_raise_irq(
        	        avr_io_getirq(
                	        avr, 
	                        AVR_IOCTL_IOPORT_GETIRQ(port[0]), 
         	                element ),
                	1 );
	}

	else if( newState == BUTTON_OFF ) {
		LOG( LOGGER_WARNING, "Pin %d OFF\n", pin );
	        avr_raise_irq(
        	        avr_io_getirq(
                	        avr, 
	                        AVR_IOCTL_IOPORT_GETIRQ(port[0]), 
         	                element ),
                	0 );
	}

	else if( newState == BUTTON_AC ) {
		LOG( LOGGER_WARNING, "Pin %d AC\n", pin );
		avr_connect_irq(
        		ac_input.irq + IRQ_AC_OUT,
		        avr_io_getirq(
        	        	   avr,
                		   AVR_IOCTL_IOPORT_GETIRQ(port[0]),
		                   element)
	        	);
	}
}

void watcher_ddr(struct avr_irq_t* irq, uint32_t value, void* closure) {
  int x = 0;
  for ( x = 0; x < 8 ; x++ ) {
    set_ddr( 
	reg_pin_to_location( 
			(char *)closure, 
			x 
			), 
	( value & ( 1 << x ) ) >= 1 
	);
  }
  renderScene();
}


static void * avr_run_thread( void * ignore) {

	int state = cpu_Running;
	while ( ( state != cpu_Done ) && ( state != cpu_Crashed ) ) {
		state = avr_run ( avr );
//		usleep( 50000 );
        }
	pthread_detach(pthread_self());
        return NULL;
}

int setupConnectivity() {

  char port[2];
  port[1] = '\0';
  if( REGISTERS == NULL ) {
    LOG( LOGGER_ERROR, "Looks like we've not loaded a core yet\n" );
    return 1;
  }
  char *ports = REGISTERS();
  if( ports == NULL ) {
    LOG( LOGGER_ERROR, "No record of which registers\n" );
    return 1;
  }

  int p = 0;
  for( p = 0 ; p < strlen(ports) ; p++ ) {
    memcpy( port, &ports[p], 1);

    // Check for DDR changes
    avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( port[0] ), IOPORT_IRQ_DIRECTION_ALL ),
		watcher_ddr, port );

    // Check for State changes on (input)
    avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( port[0] ), IOPORT_IRQ_REG_PIN ),
		watcher_state, port );

    // Check for State changes on (output)
    avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( port[0] ), IOPORT_IRQ_REG_PORT ),
		watcher_state, port );
  }

  // Setup Clock
  ac_input_init(avr, &ac_input);

  pthread_t run;
  pthread_create(&run, NULL, avr_run_thread, NULL);

  return 0;
}

