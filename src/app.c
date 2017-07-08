
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
