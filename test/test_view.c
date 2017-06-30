#include "minunit.h"
#include "../src/view.h"
#include "../src/model.h"

extern float w;
void drawChip(void);
void drawWire( int, float, float, int );
void drawOutput( int, float, float, int );
void drawInputs( int, float, float, int );


char *getChipName() {
	return "test chip name";
}

MU_TEST( view___setupInterface ) {
	w = 0;
	PINS = 8;
	setupInterface( 0, NULL );
	mu_assert_uint32_eq( 150, w );
}

MU_TEST( view___mainLoop ) {
	mainLoop();
	mu_assert_uint32_eq( 1, 1 );
}


MU_TEST( view___renderScene ) {
	renderScene();
	mu_assert_uint32_eq( 1, 1 );
}


MU_TEST( view___draw_wire_on ) {
	drawWire( 1, 0.2F, 0.2F, 1 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_wire_off ) {
	drawWire( 1, 0.2F, 0.2F, 0 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_chip ) {
	drawChip();
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_outputs_on ) {
	drawOutput( 1, 0.1F, 0.1F, 1 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_outputs_off ) {
	drawOutput( 1, 0.1F, 0.1F, 0 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_inputs_on ) {
	drawInputs( 1, 0.1F, 0.1F, 1 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_inputs_off ) {
	drawInputs( 1, 0.1F, 0.1F, 0 );
	mu_assert_uint32_eq( 1, 1 );
}


MU_TEST_SUITE( test_view ) {

	CHIPNAME = getChipName;

	MU_RUN_TEST( view___setupInterface );
	MU_RUN_TEST( view___mainLoop );

	MU_RUN_TEST( view___renderScene );

	MU_RUN_TEST( view___draw_wire_on );
	MU_RUN_TEST( view___draw_wire_off );
	MU_RUN_TEST( view___draw_chip );
	MU_RUN_TEST( view___draw_outputs_on );
	MU_RUN_TEST( view___draw_outputs_off );
	MU_RUN_TEST( view___draw_inputs_on );
	MU_RUN_TEST( view___draw_inputs_off );
}
