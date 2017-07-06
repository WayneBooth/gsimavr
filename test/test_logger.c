#include <stdlib.h>
#include <unistd.h>
#include <sim_avr.h>

#include "minunit.h"
#include "../src/logger.h"

extern logger_p _logger_routine;

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

MU_TEST( logger___LOG___null_logger_high___no_logs ) {
	unlink( "test.log" );
	_logger_routine = NULL;
	LOG( LOGGER_OUTPUT, "Hello %s", "there\n" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
}

MU_TEST( logger___LOG___no_logger_high___logs ) {
	unlink( "test.log" );
	LOG( LOGGER_OUTPUT, "Hello %s", "there\n" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log ); // Gets directed to STDOUT (how would I assert this?)
	free(log);
}

MU_TEST( logger___LOG___no_logger_low___no_logs ) {
	unlink( "test.log" );
	LOG( LOGGER_DEBUG, "Hello %s", "there\n" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log ); // Again, how would I assert this hasn't appeard on STDOUT?
	free(log);
}

MU_TEST( logger___LOG___app_set_high___logs ) {
	unlink( "test.log" );
	LOG( LOGGER_OUTPUT, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "out:61:test_logger.c:logger___LOG___app_set_high___logs: Hello there", log );
	free(log);
}

MU_TEST( logger___LOG___app_set_low___no_logs ) {
	unlink( "test.log" );
	LOG( LOGGER_DEBUG, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
}

MU_TEST( logger___LOG___no_log_level___no_logs ) {
	unlink( "test.log" );
	LOG( 100, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
}

MU_TEST( logger___AVRLOG___app_set_high___logs ) {
	unlink( "test.log" );
	AVR_LOG( NULL, LOGGER_ERROR, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "AVRLOG: Hello there", log );
	free(log);
}

MU_TEST( logger___AVRLOG___app_set_low___no_logs ) {
	unlink( "test.log" );
	AVR_LOG( NULL, LOGGER_DEBUG, "Hello %s", "there" );
	char *log = get_log_contents();
	mu_assert_string_eq( "", log );
	free(log);
}

MU_TEST_SUITE( test_logger ) {

	app_verbosity = LOGGER_WARNING;

	MU_RUN_TEST_MUTE( logger___LOG___null_logger_high___no_logs );

	set_logger( NULL );

	MU_RUN_TEST_MUTE( logger___LOG___no_logger_high___logs );
	MU_RUN_TEST_MUTE( logger___LOG___no_logger_low___no_logs );

	set_logger( (logger_p)log_capture );

	MU_RUN_TEST( logger___LOG___no_log_level___no_logs );

	MU_RUN_TEST( logger___LOG___app_set_high___logs );
	MU_RUN_TEST( logger___LOG___app_set_low___no_logs );

	MU_RUN_TEST( logger___AVRLOG___app_set_high___logs );
	MU_RUN_TEST( logger___AVRLOG___app_set_low___no_logs );

	unlink( "test.log" );
	set_logger( NULL );
}
