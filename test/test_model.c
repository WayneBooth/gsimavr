#include "minunit.h"
#include "../src/model.h"

void set_state( uint32_t *, int , int );
void set_ioState( int, int );

uint32_t expected;

uint32_t noConnection;
uint32_t powerPins;
uint32_t powerState;

uint32_t ddrPins;
uint32_t outputState;
uint32_t inputState;

MU_TEST( set_state___setOfftoOn ) {
	expected = 0b0000000000000000000000000010;
	uint32_t test_val = 0b0000000000000000000000000000;
	set_state( &test_val, 2, 1 );
	mu_assert_uint32_eq( expected, test_val );
}

MU_TEST( set_state___setOntoOff ) {
	expected = 0b0000000000000000000000000100;
	uint32_t test_val = 0b0000000000000000000000000110;
	set_state( &test_val, 2, 0 );
	mu_assert_uint32_eq( expected, test_val );
}

MU_TEST( set_ioState___output___setOntoOff ) {
	expected =    0b0000000000000000000000000010;
	ddrPins =     0b0000000000000000000000001100; // 1=output 0=input
	outputState = 0b0000000000000000000000000110;
	inputState =  0b0000000000000000000000000110;
	set_ioState( 3, 0 );
	mu_assert_uint32_eq( expected, outputState );
	mu_assert_uint32_eq( 0b0000000000000000000000000110, inputState );
}

MU_TEST( set_ioState___output___setOfftoOn ) {
	uint32_t expected = 0b00000000000000000000000000001110;
	ddrPins =     0b0000000000000000000000001100; // 1=output 0=input
	outputState = 0b0000000000000000000000000110;
	inputState =  0b0000000000000000000000000110;
	set_ioState( 4, 1 );
	mu_assert_uint32_eq( expected, outputState );
	mu_assert_uint32_eq( 0b0000000000000000000000000110, inputState );
}

MU_TEST( set_ioState___input___setOntoOff ) {
	uint32_t expected = 0b00000000000000000000000000000100;
	ddrPins =     0b0000000000000000000000001100; // 1=output 0=input
	outputState = 0b0000000000000000000000000110;
	inputState =  0b0000000000000000000000000110;
	set_ioState( 2, 0 );
	mu_assert_uint32_eq( expected, inputState );
	mu_assert_uint32_eq( 0b0000000000000000000000000110, outputState );
}

MU_TEST( set_ioState___input___setOfftoOn ) {
	uint32_t expected = 0b00000000000000000000000000000111;
	ddrPins =     0b0000000000000000000000001100; // 1=output 0=input
	outputState = 0b0000000000000000000000000110;
	inputState =  0b0000000000000000000000000110;
	set_ioState( 1, 1 );
	mu_assert_uint32_eq( expected, inputState );
	mu_assert_uint32_eq( 0b0000000000000000000000000110, outputState );
}

MU_TEST_SUITE(test_model) {

	MU_RUN_TEST( set_state___setOfftoOn );
	MU_RUN_TEST( set_state___setOntoOff );

	MU_RUN_TEST( set_ioState___output___setOntoOff );
	MU_RUN_TEST( set_ioState___output___setOfftoOn );
	MU_RUN_TEST( set_ioState___input___setOntoOff );
	MU_RUN_TEST( set_ioState___input___setOfftoOn );
}
