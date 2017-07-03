#include "minunit.h"
#include "../src/controller.h"

extern char *(*REGISTERS)();

void * avr_run_thread( void * );

char *regs = "BCD";
char *giveRegs() {
	return regs;
}

MU_TEST( controller___setupConnectivity___no_core_fails ) {
	REGISTERS = NULL;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( ret, 1 );
}

MU_TEST( controller___setupConnectivity___emptry_registers_fails ) {
	regs = NULL;
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( ret, 1 );
}

MU_TEST( controller___setupConnectivity___with_core ) {
	regs = "DFG";
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( ret, 0 );
}


MU_TEST( controller___avr_run_thread ) {
	avr_run_thread( NULL );
	mu_assert_uint32_eq( 1, 1 );
}


MU_TEST_SUITE( test_controller ) {

	MU_RUN_TEST( controller___setupConnectivity___no_core_fails );
	MU_RUN_TEST( controller___setupConnectivity___emptry_registers_fails );
	MU_RUN_TEST( controller___setupConnectivity___with_core );

	MU_RUN_TEST( controller___avr_run_thread );
}
