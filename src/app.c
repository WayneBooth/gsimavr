
#include "view.h"
#include "model.h"
#include "controller.h"

int main(int argc, char **argv) {

	setupSimulator(); // Model

	setupInterface( argc, argv ); // View

	setupConnectivity(); // Controller

	mainLoop(); // View

	return 1;
}
