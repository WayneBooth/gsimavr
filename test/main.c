#include <unistd.h>

#include "utils.h"
#include "minunit.h"
#include "../src/logger.h"

void test_logger();
void test_view();
void test_model();
void test_controller();
void test_ac_input();

MU_INIT();

int main(int argc, char *argv[]) {

        unlink( "output.log" );

	MU_RUN_SUITE( test_logger );

	app_verbosity = LOGGER_DEBUG;
	stop_capturing_log();

	MU_RUN_SUITE( test_view );
	MU_RUN_SUITE( test_model );
	MU_RUN_SUITE( test_controller );

	MU_REPORT();
	if (!minunit_status && minunit_fail) { return 1; }
	return 0;
}
 
