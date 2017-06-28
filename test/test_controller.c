#include "minunit.h"
#include "../src/controller.h"

MU_TEST( controller___setupConnectivity ) {
	setupConnectivity();
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST_SUITE( test_controller ) {

	MU_RUN_TEST( controller___setupConnectivity );
}
