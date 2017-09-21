
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "logger.h"
#include "view.h"
#include "model.h"
#include "controller.h"

int main(int argc, char **argv) {

	int opt;
	int useGdb = 0;






//	        avr_vcd_init(avr, "gtkwave_output.vcd", &vcd_file, 100000 /* usec */);
//		avr_vcd_add_signal(&vcd_file,
//			avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), IOPORT_IRQ_PIN_ALL), 8 /* bits */ ,
//			"portb" );
//		avr_vcd_add_signal(&vcd_file,
//			button.irq + IRQ_BUTTON_OUT, 1 /* bits */ ,
//			"button" );








	while ((opt = getopt(argc, argv, "dh")) != -1) {
     	   switch (opt) {
        	case 'd': 
		    useGdb = 1; 
		    break;
        	default:
	            printf("Usage: %s [-dh] [glut params]\n", argv[0]);
	            exit(EXIT_FAILURE);
	   }
	}

	app_verbosity = LOGGER_WARNING;

	if( setupSimulator( useGdb ) ) { // Model
		return 1;
	}

	setupInterface( argc, argv ); // View

	if( setupConnectivity() ) { // Controller
		return 1;
	}

	mainLoop(); // View

	return 1;
}
