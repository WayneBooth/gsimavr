#include "minunit.h"
#include "../src/controller.h"
#include "../src/model.h"

extern char *(*REGISTERS)();

extern char *array[10];
extern int avr_io_getirq_counter;
extern uint32_t outputState;
extern uint32_t ddrPins;

void watcher_state(struct avr_irq_t* irq, uint32_t value, void* closure);
void watcher_ddr(struct avr_irq_t* irq, uint32_t value, void* closure);
void createAvr( char *, char * );
void * avr_run_thread( void * );
int loadGsimavrCore( char * );

char *regs = "BCD";
char *giveRegs() {
	return regs;
}

MU_TEST( controller___watcher_state___zero ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_state( (avr_irq_t *)1, 0, "B" );
	mu_assert_uint32_eq( 0, outputState );
}

MU_TEST( controller___watcher_state___one ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_state( (avr_irq_t *)1, 1, "B" );
	// B register pin 1 is on phystical pin 14, so 2^13 = 8192
	mu_assert_uint32_eq( 8192, outputState );
}

MU_TEST( controller___watcher_state___one_twenty_eight ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_state( (avr_irq_t *)1, 128, "B" );
	// B register pin 8 (binary 128) is on phystical pin 10, so 2^9 = 512
	mu_assert_uint32_eq( 512, outputState );
}

MU_TEST( controller___watcher_ddr___zero ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_ddr( (avr_irq_t *)1, 0, "B" );
	mu_assert_uint32_eq( 265296958, ddrPins );
}

MU_TEST( controller___watcher_ddr___one ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_ddr( (avr_irq_t *)1, 1, "B" );
	mu_assert_uint32_eq( 265296958 + 8192, ddrPins );
}

MU_TEST( controller___watcher_ddr___one_twenty_eight ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	watcher_ddr( (avr_irq_t *)1, 128, "B" );
	mu_assert_uint32_eq( 265296958 + 512, ddrPins );
}

MU_TEST( controller___changeInput___pin_not_found ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	ret = changeInput( 100, BUTTON_ON );
	mu_assert_uint32_eq( 1, ret );
}

MU_TEST( controller___changeInput___pin_button_on ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	avr_io_getirq_counter = 0;
	ret = changeInput( 2, BUTTON_ON );
	mu_assert_uint32_eq( 0, ret );
	mu_assert_uint32_eq( 1, avr_io_getirq_counter );
}

MU_TEST( controller___changeInput___pin_button_off ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	avr_io_getirq_counter = 0;
	ret = changeInput( 2, BUTTON_OFF );
	mu_assert_uint32_eq( 0, ret );
	mu_assert_uint32_eq( 1, avr_io_getirq_counter );
}

MU_TEST( controller___changeInput___pin_button_ac ) {
	int ret = loadGsimavrCore( "atmega328p" );
	mu_assert_uint32_eq( 0, ret );
	avr_io_getirq_counter = 0;
	ret = changeInput( 2, BUTTON_AC );
	mu_assert_uint32_eq( 0, ret );
	mu_assert_uint32_eq( 1, avr_io_getirq_counter );
}

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
	createAvr( WRAPPEDFIRMWARENAME, WRAPPEDFIRMWAREMCU );
	regs = "DFA";
	REGISTERS = giveRegs;
	int ret = setupConnectivity();
	mu_assert_uint32_eq( 0, ret );
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

	MU_RUN_TEST( controller___watcher_state___zero );
	MU_RUN_TEST( controller___watcher_state___one );
	MU_RUN_TEST( controller___watcher_state___one_twenty_eight );
	MU_RUN_TEST( controller___watcher_ddr___zero );
	MU_RUN_TEST( controller___watcher_ddr___one );
	MU_RUN_TEST( controller___watcher_ddr___one_twenty_eight );

	MU_RUN_TEST( controller___changeInput___pin_not_found );
	MU_RUN_TEST( controller___changeInput___pin_button_on );
	MU_RUN_TEST( controller___changeInput___pin_button_off );
	MU_RUN_TEST( controller___changeInput___pin_button_ac );

	MU_RUN_TEST( controller___setupConnectivity___no_core_fails );
	MU_RUN_TEST( controller___setupConnectivity___emptry_registers_fails );
	MU_RUN_TEST( controller___setupConnectivity___with_core );

	MU_RUN_TEST( controller___avr_run_thread );
}
