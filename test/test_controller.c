#include "minunit.h"
#include "../src/controller.h"

extern char *(*REGISTERS)();

extern char *array[10];

void * avr_run_thread( void * );
int loadGsimavrCore( char * );

char *regs = "BCD";
char *giveRegs() {
	return regs;
}

MU_TEST( controller___changeInput___ping_not_found ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( ret, 1 );
	ret = changeInput( 100, BUTTON_ON );
	mu_assert_uint32_eq( ret, 1 );
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
	regs = "DFA";
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( ret, 0 );
	mu_assert_string_eq( array[0], "D" );
	mu_assert_string_eq( array[1], "D" );
	mu_assert_string_eq( array[2], "D" );
	mu_assert_string_eq( array[3], "F" );
	mu_assert_string_eq( array[4], "F" );
	mu_assert_string_eq( array[5], "F" );
	mu_assert_string_eq( array[6], "A" );
	mu_assert_string_eq( array[7], "A" );
	mu_assert_string_eq( array[8], "A" );
	mu_assert_string_eq( array[9], NULL );
}


MU_TEST( controller___avr_run_thread ) {
	avr_run_thread( NULL );
	mu_assert_uint32_eq( 1, 1 );
}


MU_TEST_SUITE( test_controller ) {

	MU_RUN_TEST( controller___changeInput___ping_not_found );

	MU_RUN_TEST( controller___setupConnectivity___no_core_fails );
	MU_RUN_TEST( controller___setupConnectivity___emptry_registers_fails );
	MU_RUN_TEST( controller___setupConnectivity___with_core );

	MU_RUN_TEST( controller___avr_run_thread );
}
