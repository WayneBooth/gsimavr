#include "minunit.h"
#include "../src/ac_input.h"

MU_TEST( ac_input_pass ) {
	mu_assert_uint32_eq( 1, 1 );
}

MU_TEST_SUITE( test_ac_input ) {

	MU_RUN_TEST( ac_input_pass );
}
