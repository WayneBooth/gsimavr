#include "minunit.h"
#include <GL/glut.h>
#include "../src/view.h"
#include "../src/model.h"

extern float w;
extern float pins[28][4];
void drawChip(void);
void drawWire( int, float, float, int );
void drawOutput( int, float, float, int );
void drawInputs( int, float, float, int );
void mouseFunc( int, int, int, int );
void changeSize(int, int);

char *getChipName() {
	return "test chip name";
}

extern char *(*REGISTERS)();
int gotHere = 0;
char *dummyRegs() {
  gotHere = 1;
  return "";
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

MU_TEST( view___changeSize ) {
	changeSize( 5, 5 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___mouseFunc ) {
	gotHere = 0;
	REGISTERS = dummyRegs;
	pins[1][0] = 4;
	pins[1][1] = 4;
	pins[1][2] = 6;
	pins[1][3] = 6;
	mouseFunc( 0, GLUT_DOWN, 5, 5);
	mouseFunc( 0, GLUT_UP, 5, 5);
	mu_assert_uint32_eq( 1, gotHere );
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
	MU_RUN_TEST( view___changeSize );
	MU_RUN_TEST( view___mouseFunc );

	MU_RUN_TEST( view___draw_wire_on );
	MU_RUN_TEST( view___draw_wire_off );
	MU_RUN_TEST( view___draw_chip );
	MU_RUN_TEST( view___draw_outputs_on );
	MU_RUN_TEST( view___draw_outputs_off );
	MU_RUN_TEST( view___draw_inputs_on );
	MU_RUN_TEST( view___draw_inputs_off );

}
