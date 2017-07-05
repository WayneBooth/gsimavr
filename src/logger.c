
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

static void std_logger( const char * format, va_list ap);
static logger_p _logger_routine = std_logger;

const char *level_human( const int level ) {
	switch( level ) {
		case LOGGER_NONE:
		      return "non";
		case LOGGER_OUTPUT:
		      return "out";
		case LOGGER_ERROR:
		      return "err";
		case LOGGER_WARNING:
		      return "wrn";
		case LOGGER_TRACE:
		      return "trc";
		case LOGGER_DEBUG:
		      return "dbg";
		default:
		      return "";
	}
}

void logger_routine( const char * func, char * file, int line, int level, const char * format, ... ) {
	va_list args;
	va_start(args, format);
	if ( _logger_routine ) {
		if ( app_verbosity >= level ) {
                	int len = snprintf(NULL, 0, "%s:%d:%s:%s: %s", level_human(level), line, file, func, format );
                	char *st = (char *)malloc(len+1);
                	snprintf(st, len+1, "%s:%d:%s:%s: %s", level_human(level), line, file, func, format );
			_logger_routine( st, args );
			free(st);
		}
	}
	va_end(args);
}

void set_logger( logger_p logger ) {
	_logger_routine = logger ? logger : &std_logger;
}

static void std_logger( const char * format, va_list ap ) {
	vprintf( format, ap);
}

void gsimavr_avr_logger( const int level, const char * format, va_list ap ) {
        if ( app_verbosity >= level ) {
                int len = snprintf(NULL, 0, "AVRLOG: %s", format );
                char *st = (char *)malloc(len+1);
                snprintf(st, len+1, "AVRLOG: %s", format );
                _logger_routine( st, ap );
                free(st);
        }
}
