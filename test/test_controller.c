#include "minunit.h"
#include "../src/controller.h"
#include "../src/model.h"

#include <stdlib.h>

extern char *(*REGISTERS)();

extern char *ports;
extern char array[33];
extern int avr_io_getirq_counter;
extern uint32_t outputState;
extern uint32_t ddrPins;

void watcher_state_out(struct avr_irq_t* irq, uint32_t value, void* closure);
void watcher_ddr(struct avr_irq_t* irq, uint32_t value, void* closure);
void createAvr( char *, char *, char * );
void * avr_run_thread( void * );
int loadGsimavrCore( char * );

avr_irq_t * mirq;
char *regs = "BCD";
char *giveRegs() {
	return regs;
}

MU_TEST( controller___watcher_state_out___zero ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_state_out( (avr_irq_t *)mirq, 0, "B" );
	mu_assert_uint32_eq( 0, outputState );
}

MU_TEST( controller___watcher_state_out___one ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_state_out( (avr_irq_t *)mirq, 1, "B" );
	// B register pin 1 is on phystical pin 14, so 2^13 = 8192
	mu_assert_uint32_eq( 8192, outputState );
}

MU_TEST( controller___watcher_state_out___one_twenty_eight ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_state_out( (avr_irq_t *)mirq, 128, "B" );
	// B register pin 8 (binary 128) is on phystical pin 10, so 2^9 = 512
	mu_assert_uint32_eq( 512, outputState );
}

MU_TEST( controller___watcher_ddr___zero ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_ddr( (avr_irq_t *)mirq, 0, "B" );
	mu_assert_uint32_eq( 265296958, ddrPins );
}

MU_TEST( controller___watcher_ddr___one ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_ddr( (avr_irq_t *)mirq, 1, "B" );
	mu_assert_uint32_eq( 265296958 + 8192, ddrPins );
}

MU_TEST( controller___watcher_ddr___one_twenty_eight ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_ddr( (avr_irq_t *)mirq, 128, "B" );
	mu_assert_uint32_eq( 265296958 + 512, ddrPins );
}

MU_TEST( controller___changeInput___pin_not_found ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	ports = "BCD";
	ret = changeInput( 100, BUTTON_ON );
	mu_assert_uint32_eq( 1, ret );
	ports = NULL;
}

MU_TEST( controller___changeInput___pin_button_on ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	avr_io_getirq_counter = 0;
	ports = "BCD";
	ret = changeInput( 2, BUTTON_ON );
	mu_assert_uint32_eq( 0, ret );
	mu_assert_uint32_eq( 1, avr_io_getirq_counter );
	ports = NULL;
}

MU_TEST( controller___changeInput___pin_button_off ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	avr_io_getirq_counter = 0;
	ports = "BCD";
	ret = changeInput( 2, BUTTON_OFF );
	mu_assert_uint32_eq( 0, ret );
	mu_assert_uint32_eq( 1, avr_io_getirq_counter );
	ports = NULL;
}

/*
MU_TEST( controller___changeInput___pin_button_ac ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	avr_io_getirq_counter = 0;
	ports = "BCD";
	ret = changeInput( 2, BUTTON_AC );
	mu_assert_uint32_eq( 0, ret );
	mu_assert_uint32_eq( 1, avr_io_getirq_counter );
	ports = NULL;
}
*/

MU_TEST( controller___setupConnectivity___no_core_fails ) {
	REGISTERS = NULL;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( 1, ret );
}

MU_TEST( controller___setupConnectivity___emptry_registers_fails ) {
	regs = NULL;
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( 1, ret );
}

MU_TEST( controller___setupConnectivity___with_core ) {
	createAvr( WRAPPEDFIRMWAREDIR, WRAPPEDFIRMWARENAME, WRAPPEDFIRMWAREMCU );
	regs = "DFA";
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( 0, ret );
	mu_assert_int8_eq( 'D', array[0] );
	mu_assert_int8_eq( 'D', array[1] );
	mu_assert_int8_eq( 'F', array[2] );
	mu_assert_int8_eq( 'F', array[3] );
	mu_assert_int8_eq( 'A', array[4] );
	mu_assert_int8_eq( 'A', array[5] );
	mu_assert_int8_eq( '\0', array[6] );
/*	mu_assert_int8_eq( array[6], 'D' );
	mu_assert_int8_eq( array[7], 'D' );
	mu_assert_int8_eq( array[8], 'D' );
	mu_assert_int8_eq( array[9], 'D' );
	mu_assert_int8_eq( array[10], 'F' );
	mu_assert_int8_eq( array[11], 'F' );
	mu_assert_int8_eq( array[12], 'F' );
	mu_assert_int8_eq( array[13], 'F' );
	mu_assert_int8_eq( array[14], 'F' );
	mu_assert_int8_eq( array[15], 'F' );
	mu_assert_int8_eq( array[16], 'F' );
	mu_assert_int8_eq( array[17], 'F' );
	mu_assert_int8_eq( array[18], 'F' );
	mu_assert_int8_eq( array[19], 'F' );
	mu_assert_int8_eq( array[20], 'A' );
	mu_assert_int8_eq( array[21], 'A' );
	mu_assert_int8_eq( array[22], 'A' );
	mu_assert_int8_eq( array[23], 'A' );
	mu_assert_int8_eq( array[24], 'A' );
	mu_assert_int8_eq( array[25], 'A' );
	mu_assert_int8_eq( array[26], 'A' );
	mu_assert_int8_eq( array[27], 'A' );
	mu_assert_int8_eq( array[28], 'A' );
	mu_assert_int8_eq( array[29], 'A' );
	mu_assert_int8_eq( array[30], '\0' );
*/
}


MU_TEST( controller___avr_run_thread ) {
	avr_run_thread( NULL );
	mu_assert_uint32_eq( 1, 1 );
}


MU_TEST_SUITE( test_controller ) {

	mirq = (avr_irq_t*)malloc(sizeof(avr_irq_t) * 1);
	mirq->irq = 1;

	MU_RUN_TEST( controller___watcher_state_out___zero );
	MU_RUN_TEST( controller___watcher_state_out___one );
	MU_RUN_TEST( controller___watcher_state_out___one_twenty_eight );
	MU_RUN_TEST( controller___watcher_ddr___zero );
	MU_RUN_TEST( controller___watcher_ddr___one );
	MU_RUN_TEST( controller___watcher_ddr___one_twenty_eight );

	MU_RUN_TEST( controller___changeInput___pin_not_found );
	MU_RUN_TEST( controller___changeInput___pin_button_on );
	MU_RUN_TEST( controller___changeInput___pin_button_off );
	//MU_RUN_TEST( controller___changeInput___pin_button_ac );

	MU_RUN_TEST( controller___setupConnectivity___no_core_fails );
	MU_RUN_TEST( controller___setupConnectivity___emptry_registers_fails );
	MU_RUN_TEST( controller___setupConnectivity___with_core );

	MU_RUN_TEST( controller___avr_run_thread );

	free( mirq );
}
