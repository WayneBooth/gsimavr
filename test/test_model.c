#include "minunit.h"
#include "../src/model.h"

void set_state( uint32_t *, int , int );
void set_ioState( int, int );
int voidPtr_to_int( void * );
void createAvr( char *, char *);
void setupGdb( int );
int loadGsimavrCore( char * );

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

MU_TEST( set_ddr___setOfftoOn ) {
	expected = 0b0000000000000000000000001110;
	ddrPins =  0b0000000000000000000000001100; // 1=output 0=input
	set_ddr( 2, 1 );
	mu_assert_uint32_eq( expected, ddrPins );
}

MU_TEST( set_ddr___setOntoOff ) {
	expected = 0b0000000000000000000000000100;
	ddrPins =  0b0000000000000000000000001100; // 1=output 0=input
	set_ddr( 4, 0 );
	mu_assert_uint32_eq( expected, ddrPins );
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

MU_TEST( voidPtr_to_int___undef ) {
	int input = '\0';
	void *ptr = &input;
	int output = voidPtr_to_int( ptr );
	mu_assert( output == 0, "Output incorrectly is not zero" );
}

MU_TEST( voidPtr_to_int___string ) {
	char *input = "Some string\0";
	void *ptr = input;
	int output = voidPtr_to_int( ptr );
	mu_assert( output == 1701670739, "Output incorrectly is not int int value of the string" );
}

MU_TEST( voidPtr_to_int___int ) {
	int input = 12345;
	void *ptr = &input;
	int output = voidPtr_to_int( ptr );
	mu_assert( output == 12345, "Output incorrectly is not 12345" );
}

MU_TEST( setupSimulator___fails ) {
	int ret = setupSimulator( 1 );
	mu_assert( ret == 1, "setupSimulator expected to fail with '1'" );
}

MU_TEST( createAvr___completes ) {
	createAvr( WRAPPEDFIRMWARENAME, WRAPPEDFIRMWAREMCU );
	mu_assert( 1 == 1, "createAvr did not complete" );
}

MU_TEST( setupGdb___completes ) {
	setupGdb( 1 );
	mu_assert( 1 == 1, "setupGdn did not complete" );
}

MU_TEST( loadGsimavrCore___fails ) {
	int ret = loadGsimavrCore( "UNKNOWN" );
	mu_assert( ret == 1, "loadGsimavrCore did not fail as expected" );
}

MU_TEST( loadGsimavrCore___completes ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert( ret == 0, "loadGsimavrCore did not complete" );
}

MU_TEST_SUITE( test_model ) {

	MU_RUN_TEST( set_state___setOfftoOn );
	MU_RUN_TEST( set_state___setOntoOff );

	MU_RUN_TEST( set_ddr___setOfftoOn );
	MU_RUN_TEST( set_ddr___setOntoOff );

	MU_RUN_TEST( set_ioState___output___setOntoOff );
	MU_RUN_TEST( set_ioState___output___setOfftoOn );
	MU_RUN_TEST( set_ioState___input___setOntoOff );
	MU_RUN_TEST( set_ioState___input___setOfftoOn );

	MU_RUN_TEST( voidPtr_to_int___undef );
	MU_RUN_TEST( voidPtr_to_int___string );
	MU_RUN_TEST( voidPtr_to_int___int );

	MU_RUN_TEST( setupSimulator___fails );
	MU_RUN_TEST( createAvr___completes );
	MU_RUN_TEST( setupGdb___completes );
	MU_RUN_TEST( loadGsimavrCore___fails );
	MU_RUN_TEST( loadGsimavrCore___completes );
}
