#include "minunit.h"
#include "../src/view.h"

MU_TEST( view_pass ) {
	setupInterface( 0, NULL );
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST_SUITE( test_view ) {

	MU_RUN_TEST( view_pass );
}
