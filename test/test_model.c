#include "minunit.h"
#include "../src/model.h"

void set_state( uint32_t *, int , int );

MU_TEST( set_state___setOfftoOn ) {
	uint32_t expected = 0b00000000000000000000000000000010;
	uint32_t test_val = 0b00000000000000000000000000000000;
	set_state( &test_val, 2, 1 );
	mu_assert_uint32_eq( expected, test_val );
}

MU_TEST( set_state___setOntoOff ) {
	uint32_t expected = 0b00000000000000000000000000000000;
	uint32_t test_val = 0b00000000000000000000000000000010;
	set_state( &test_val, 2, 0 );
	mu_assert_uint32_eq( expected, test_val );
}


MU_TEST_SUITE(test_model) {

	MU_RUN_TEST( set_state___setOfftoOn );
	MU_RUN_TEST( set_state___setOntoOff );
}
