#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"
#include "../src/logger.h"

void logtofile( const char * format, va_list ap) {
	FILE *fp = fopen("output.log", "a");
	vfprintf( fp, format, ap );
	fclose( fp );
}

void log_capture( const char * format, va_list ap) {
	FILE *fp = fopen("test.log", "a");
	vfprintf( fp, format, ap );
	fclose( fp );
	logtofile( format, ap );
}

void start_capturing_log( logger_p logger ) {
	set_logger( logger );
	unlink("test.log");
}

void start_capturing_log_std() {
	start_capturing_log( (logger_p)log_capture );
}

void stop_capturing_log() {
	set_logger( (logger_p)logtofile );
	unlink("test.log");
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

