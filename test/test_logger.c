#include <stdlib.h>
#include <unistd.h>
#include <sim_avr.h>

#include "minunit.h"
#include "../src/logger.h"

void log_capture( const char * format, va_list ap) {
	FILE *fp = fopen("test.log", "a");
	vfprintf( fp, format, ap );
	fclose( fp );
}

char *get_log_contents() {
	FILE *fp = fopen("test.log", "r");
	if( fp ) {
		fseek(fp, 0, SEEK_END);
		int string_size = ftell(fp);
		rewind(fp);
		char* buff = (char *)malloc( sizeof(char) * (string_size + 1) );
		int read_size = fread( buff, sizeof(char), string_size, fp );
		buff[string_size] = '\0';
		if( string_size != read_size ) {
			buff[0] = '\0';
		}
		fclose( fp );
		return buff;
	}
	return strdup("");
}

MU_TEST( logger___LOG___logs ) {
	unlink( "test.log" );
	LOG( LOGGER_OUTPUT, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "Hello there", log );
	free(log);
}

MU_TEST( logger___LOG___no_logs ) {
	unlink( "test.log" );
	LOG( LOGGER_DEBUG, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
}

MU_TEST( logger___AVRLOG___no_object___avr_logs_and_gsimavr_logs ) {
	// 
	unlink( "test.log" );
	// No AVR, so AVR_LOG will always log
	// LOGGER_OUTPUT is lower than app_verbosity - so LOG
	AVR_LOG( NULL, LOGGER_OUTPUT, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "AVRLOG: Hello there", log );
	free(log);
}

MU_TEST( logger___AVRLOG___avr_set_low___no_logs ) {
	unlink( "test.log" );
	avr_t avr;
	avr.log = LOG_ERROR;
	// AVR logging is LOGGER_ERROR, so wont pass on LOGGER_DEBUG - no LOG
	AVR_LOG( &avr, LOG_DEBUG, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
}

MU_TEST( logger___AVRLOG___avr_set_high___avr_logs_and_gsimavr_logs ) {
	unlink( "test.log" );
	avr_t avr;
	avr.log = LOG_DEBUG;
	AVR_LOG( &avr, LOG_WARNING, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "AVRLOG: Hello there", log );
	free(log);
}

MU_TEST( logger___AVRLOG___avr_set_high_app_set_low___avr_logs_and_gsimavr_lets_anything_log ) {
	unlink( "test.log" );
	avr_t avr;
	avr.log = LOG_DEBUG;
	AVR_LOG( &avr, LOG_TRACE, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "AVRLOG: Hello there", log );
	free(log);
}

MU_TEST_SUITE( test_logger ) {

	app_verbosity = LOGGER_WARNING;
	set_logger( (logger_p)log_capture );

	MU_RUN_TEST( logger___LOG___logs );
	MU_RUN_TEST( logger___LOG___no_logs );

	MU_RUN_TEST( logger___AVRLOG___no_object___avr_logs_and_gsimavr_logs );
	MU_RUN_TEST( logger___AVRLOG___avr_set_low___no_logs );
	MU_RUN_TEST( logger___AVRLOG___avr_set_high___avr_logs_and_gsimavr_logs );
	MU_RUN_TEST( logger___AVRLOG___avr_set_high_app_set_low___avr_logs_and_gsimavr_lets_anything_log );

	set_logger( NULL );
}
