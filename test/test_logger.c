#include <stdlib.h>
#include <unistd.h>
#include <sim_avr.h>

#include "minunit.h"
#include "utils.h"
#include "../src/logger.h"

MU_TEST( logger___LOG___null_logger_high___no_logs ) {
	start_capturing_log( NULL );
	_logger_routine = NULL;
	LOG( LOGGER_OUTPUT, "Hello %s", "there\n" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___LOG___no_logger_high___logs ) {
	start_capturing_log( NULL );
	LOG( LOGGER_OUTPUT, "Hello %s", "there\n" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log ); // Gets directed to STDOUT (how would I assert this?)
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___LOG___no_logger_low___no_logs ) {
	start_capturing_log( NULL );
	LOG( LOGGER_DEBUG, "Hello %s", "there\n" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log ); // Again, how would I assert this hasn't appeard on STDOUT?
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___LOG___app_set_high___logs ) {
	start_capturing_log_std();
	LOG( LOGGER_OUTPUT, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "out:39:test_logger.c:logger___LOG___app_set_high___logs: Hello there", log );
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___LOG___app_set_low___no_logs ) {
	start_capturing_log_std();
	LOG( LOGGER_DEBUG, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___LOG___no_log_level___no_logs ) {
	start_capturing_log_std();
	LOG( 100, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___AVRLOG___app_set_high___logs ) {
	start_capturing_log_std();
	AVR_LOG( NULL, LOGGER_ERROR, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "AVRLOG: Hello there", log );
	free(log);
	stop_capturing_log();
}

MU_TEST( logger___AVRLOG___app_set_low___no_logs ) {
	start_capturing_log_std();
	AVR_LOG( NULL, LOGGER_DEBUG, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
	stop_capturing_log();
}

MU_TEST_SUITE( test_logger ) {

	app_verbosity = LOGGER_WARNING;

	MU_RUN_TEST_MUTE( logger___LOG___null_logger_high___no_logs );

	//set_logger( NULL );

	MU_RUN_TEST_MUTE( logger___LOG___no_logger_high___logs );
	MU_RUN_TEST_MUTE( logger___LOG___no_logger_low___no_logs );

	//set_logger( (logger_p)log_capture );

	MU_RUN_TEST( logger___LOG___no_log_level___no_logs );

	MU_RUN_TEST( logger___LOG___app_set_high___logs );
	MU_RUN_TEST( logger___LOG___app_set_low___no_logs );

	MU_RUN_TEST( logger___AVRLOG___app_set_high___logs );
	MU_RUN_TEST( logger___AVRLOG___app_set_low___no_logs );

	//unlink( "test.log" );
	//set_logger( NULL );
}
