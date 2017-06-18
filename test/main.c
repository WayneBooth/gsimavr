#include "minunit.h"

void test_view();
void test_model();
void test_controller();
void test_ac_input();

MU_INIT();

int main(int argc, char *argv[]) {

	MU_RUN_SUITE( test_view );
	MU_RUN_SUITE( test_model );
	MU_RUN_SUITE( test_controller );
	MU_RUN_SUITE( test_ac_input );

	MU_REPORT();
	if (!minunit_status && minunit_fail) { return 1; }
	return 0;
}
 
