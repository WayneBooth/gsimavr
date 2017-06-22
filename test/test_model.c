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

MU_TEST( loadGsimavrCore___unknown___fails ) {
	int ret = loadGsimavrCore( "UNKNOWN" );
	mu_assert( ret == 1, "loadGsimavrCore did not fail as expected" );
}

MU_TEST( loadGsimavrCore___atmega328p___completes ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert( ret == 0, "loadGsimavrCore did not complete" );
	mu_assert( PINS == 28, "Device does not report 28 pins" );
}

MU_TEST( reg_pin_to_location___port_A ) {
	int pin = reg_pin_to_location( "A", 0 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "A", 1 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "A", 2 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "A", 3 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "A", 4 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "A", 5 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "a", 6 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "a", 7 );
	mu_assert( pin == 0, "Incorrect pin reference" );
}

MU_TEST( reg_pin_to_location___port_B ) {
	int pin = reg_pin_to_location( "B", 0 );
	mu_assert( pin == 14, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 1 );
	mu_assert( pin == 15, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 2 );
	mu_assert( pin == 16, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 3 );
	mu_assert( pin == 17, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 4 );
	mu_assert( pin == 18, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 5 );
	mu_assert( pin == 19, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 6 );
	mu_assert( pin == 9, "Incorrect pin reference" );
	pin = reg_pin_to_location( "B", 7 );
	mu_assert( pin == 10, "Incorrect pin reference" );
}

MU_TEST( reg_pin_to_location___port_C ) {
	int pin = reg_pin_to_location( "C", 0 );
	mu_assert( pin == 23, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 1 );
	mu_assert( pin == 24, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 2 );
	mu_assert( pin == 25, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 3 );
	mu_assert( pin == 26, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 4 );
	mu_assert( pin == 27, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 5 );
	mu_assert( pin == 28, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 6 );
	mu_assert( pin == 1, "Incorrect pin reference" );
	pin = reg_pin_to_location( "C", 7 );
	mu_assert( pin == 0, "Incorrect pin reference" );
}

MU_TEST( reg_pin_to_location___port_D ) {
	int pin = reg_pin_to_location( "D", 0 );
	mu_assert( pin == 2, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 1 );
	mu_assert( pin == 3, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 2 );
	mu_assert( pin == 4, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 3 );
	mu_assert( pin == 5, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 4 );
	mu_assert( pin == 6, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 5 );
	mu_assert( pin == 11, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 6 );
	mu_assert( pin == 12, "Incorrect pin reference" );
	pin = reg_pin_to_location( "D", 7 );
	mu_assert( pin == 13, "Incorrect pin reference" );
}

MU_TEST( reg_pin_to_location___port_E ) {
	int pin = reg_pin_to_location( "E", 0 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 1 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 2 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 3 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 4 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 5 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 6 );
	mu_assert( pin == 0, "Incorrect pin reference" );
	pin = reg_pin_to_location( "E", 7 );
	mu_assert( pin == 0, "Incorrect pin reference" );
}

MU_TEST( unloadCore___completes ) {
	unloadCore();
	mu_assert( PINS == 2, "Device does not report 2 pins" );
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

	MU_RUN_TEST( loadGsimavrCore___unknown___fails );

	MU_RUN_TEST( loadGsimavrCore___atmega328p___completes );
	MU_RUN_TEST( reg_pin_to_location___port_A );
	MU_RUN_TEST( reg_pin_to_location___port_B );
	MU_RUN_TEST( reg_pin_to_location___port_C );
	MU_RUN_TEST( reg_pin_to_location___port_D );
	MU_RUN_TEST( reg_pin_to_location___port_E );
	MU_RUN_TEST( unloadCore___completes );

}
