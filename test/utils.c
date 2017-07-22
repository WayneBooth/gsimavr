#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include "utils.h"
#include "../src/logger.h"

void logtofile( const char * format, va_list ap) {
	printf ( "format = '%s'\n", format );
	FILE *fpo = fopen("outputlog.log", "a");
	if( fpo != NULL ) {
		vprintf( format, ap );
		vfprintf( fpo, format, ap );
		fclose( fpo );
	}
	else {
		printf( "Error %s\n", strerror(errno) );
	}
}

void log_capture( const char * format, va_list ap) {
	FILE *fpt = fopen("test.log", "a");
	vfprintf( fpt, format, ap );
	fclose( fpt );
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
	FILE *fpg = fopen("test.log", "r");
	if( fpg ) {
		fseek(fpg, 0, SEEK_END);
		int string_size = ftell(fpg);
		rewind(fpg);
		char* buff = (char *)malloc( sizeof(char) * (string_size + 1) );
		int read_size = fread( buff, sizeof(char), string_size, fpg );
		buff[string_size] = '\0';
		if( string_size != read_size ) {
			buff[0] = '\0';
		}
		fclose( fpg );
		return buff;
	}
	return NULL;
}

