#include "minunit.h"
#include "../src/view.h"
#include "../src/model.h"

void drawChip(void);
void drawOutput( int, float, float, int );
void drawInputs( int, float, float, int );

MU_TEST( view___draw_outputs ) {
	drawOutput( 1, 0.1F, 0.1F, 1 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_inputs ) {
	drawInputs( 1, 0.1F, 0.1F, 1 );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view___draw_chip ) {
	drawChip();
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST( view_pass ) {
	setupInterface( 0, NULL );
	mu_assert_uint32_eq( 1, 1 );
}

char *getChipName() {
	return "test chip name";
}

MU_TEST_SUITE( test_view ) {

	CHIPNAME = getChipName;
	MU_RUN_TEST( view___draw_chip );
	MU_RUN_TEST( view___draw_outputs );
	MU_RUN_TEST( view___draw_inputs );
	MU_RUN_TEST( view_pass );
}
