#include "minunit.h"
#include "../src/view.h"
#include "../src/model.h"

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
	MU_RUN_TEST( view_pass );
}
