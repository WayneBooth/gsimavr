
#include "view.h"
#include "model.h"
#include "controller.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <avr_ioport.h>
#include "ac_input.h"
#include "avr_ioport.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

ac_input_t ac_input;

enum {
	BUTTON_ON = 0,
	BUTTON_AC,
	BUTTON_OFF
};

void watcher_state(struct avr_irq_t* irq, uint32_t value, void* closure) {
  for ( int x = 0; x < 8 ; x++ ) {
    set_ioState( 
	reg_pin_to_location( 
			(char *)closure, 
			x 
			), 
	( value & ( 1 << x ) ) >= 1 
	);
  }
  renderScene();
}

void changeInput( int pin, int newState ) {

	char port[2];
	int element;
	port[1] = '\0';

	char *ports = "BCD";
	for( int p = 0 ; p < 3 ; p++ ) {
		memcpy( port, &ports[p], 1);
		for( int e = 0 ; e < 8 ; e++ ) {
			element = e;
			if( reg_pin_to_location( port, element ) == pin ) {
				printf( "You clicked %s%d\n", port, element);
				goto end;
			}
		}
	}

end:

	printf( "state = %d\n", newState );
	avr_unconnect_irq(
        	ac_input.irq + IRQ_AC_OUT,
		avr_io_getirq(
        	        	avr,
                		AVR_IOCTL_IOPORT_GETIRQ(port[0]),
		                element)
		);

	if( newState == BUTTON_ON ) {
		printf( "Pin %d POrt %c%d ON\n", pin, port[0], element );
	        avr_raise_irq(
        	        avr_io_getirq(
                	        avr, 
	                        AVR_IOCTL_IOPORT_GETIRQ(port[0]), 
         	                element ),
                	1 );
		set_ioState( 
			reg_pin_to_location( 
					port, 
					element
				), 
			1 );

	}

	else if( newState == BUTTON_OFF ) {
		printf( "Pin %d OFF\n", pin );
	        avr_raise_irq(
        	        avr_io_getirq(
                	        avr, 
	                        AVR_IOCTL_IOPORT_GETIRQ(port[0]), 
         	                element ),
                	0 );
		set_ioState( 
			reg_pin_to_location( 
					port, 
					element
				), 
			0 );
	}

	else if( newState == BUTTON_AC ) {
		printf( "Pin %d AC\n", pin );
		avr_connect_irq(
        		ac_input.irq + IRQ_AC_OUT,
		        avr_io_getirq(
        	        	   avr,
                		   AVR_IOCTL_IOPORT_GETIRQ(port[0]),
		                   element)
	        	);
		set_ioState( 
			reg_pin_to_location( 
					port, 
					element
				), 
			0 );
	}
}

void watcher_ddr(struct avr_irq_t* irq, uint32_t value, void* closure) {
  for ( int x = 0; x < 8 ; x++ ) {
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

void setupConnectivity() {


  // Check for DDR changes
  avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( 'B' ), IOPORT_IRQ_DIRECTION_ALL ),
		watcher_ddr, "B" );
  avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( 'C' ), IOPORT_IRQ_DIRECTION_ALL ),
		watcher_ddr, "C" );
  avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( 'D' ), IOPORT_IRQ_DIRECTION_ALL ),
		watcher_ddr, "D" );

  // Check for State changes
  avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( 'B' ), IOPORT_IRQ_PIN_ALL ),
		watcher_state, "B" );
  avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( 'C' ), IOPORT_IRQ_PIN_ALL ),
		watcher_state, "C" );
  avr_irq_register_notify( 
  		avr_io_getirq( avr, AVR_IOCTL_IOPORT_GETIRQ( 'D' ), IOPORT_IRQ_PIN_ALL ),
		watcher_state, "D" );


  // Watch output
//  avr_irq_register_notify(
//        avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), 0),
//        watcher, "B");
//
  // Setup Clock
  ac_input_init(avr, &ac_input);

  pthread_t run;
  pthread_create(&run, NULL, avr_run_thread, NULL);


  
  }

