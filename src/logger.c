
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

static void std_logger( const char * format, va_list ap);
static logger_p _logger_routine = std_logger;

void logger_routine( const int level, const char * format, ... ) {
	va_list args;
	va_start(args, format);
	if ( _logger_routine && app_verbosity >= level ) {
		_logger_routine( format, args);
	}
	va_end(args);
}

void set_logger( logger_p logger ) {
	_logger_routine = logger ? logger : std_logger;
}

static void std_logger( const char * format, va_list ap ) {
	vprintf( format, ap);
}

void gsimavr_avr_logger( avr_t* avr, const int level, const char * format, va_list ap ) {
        if (!avr || avr->log >= level) {
                int len = snprintf(NULL, 0, "AVRLOG: %s", format );
                char *st = (char *)malloc(len+1);
                snprintf(st, len+1, "AVRLOG: %s", format );
//vprintf( st, ap);
                _logger_routine( st, ap );
                free(st);
        }
}
