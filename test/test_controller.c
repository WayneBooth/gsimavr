#include "minunit.h"
#include "../src/controller.h"

extern char *(*REGISTERS)();

char *regs = "BCD";
char *giveRegs() {
	return regs;
}

MU_TEST( controller___setupConnectivity___no_core_fails ) {
	int ret = setupConnectivity();
	mu_assert_uint32_eq( ret, 1 );
}

MU_TEST( controller___setupConnectivity___with_core ) {
	regs = "DFG";
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( ret, 0 );
}


MU_TEST_SUITE( test_controller ) {

	MU_RUN_TEST( controller___setupConnectivity___no_core_fails );
	MU_RUN_TEST( controller___setupConnectivity___with_core );
}
