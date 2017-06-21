
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
        	case 'h':
	            printf("Usage: %s [-dh] [glut params]\n", argv[0]);
	            exit(EXIT_FAILURE);
	   }
	}

	if( setupSimulator( useGdb ) ) { // Model
		return 1;
	}

	setupInterface( argc, argv ); // View

	setupConnectivity(); // Controller

	mainLoop(); // View

	return 1;
}
