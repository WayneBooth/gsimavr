
#include <stdio.h>

#include "logger.h"

static void std_logger( const int level, const char * format, va_list ap);
static logger_p _logger_routine = std_logger;

void logger_routine( const int level, const char * format, ... ) {
	va_list args;
	va_start(args, format);
	if ( _logger_routine )
		_logger_routine( level, format, args);
	va_end(args);
}

void set_logger( logger_p logger ) {
	_logger_routine = logger ? logger : std_logger;
}

static void std_logger( const int level, const char * format, va_list ap) {
	if ( app_verbosity >= level) {
		vprintf( format, ap);
	}
}

