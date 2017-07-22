
#ifndef ___LOGGER_H___
#define ___LOGGER_H___

#include <stdarg.h>

enum {
        LOGGER_NONE = 0,//
        LOGGER_OUTPUT,	//	<-|
        LOGGER_ERROR,	//	<-|
        LOGGER_WARNING,	//	<-| <- set app verbosotry hear to get everything lower
        LOGGER_DEBUG,	//
        LOGGER_TRACE,	//
};

typedef void (*logger_p)( const char * format, va_list ap );

void set_logger( logger_p );

#define LOG(level, ...) \
        do { \
                logger_routine( __FUNCTION__, __FILE__, __LINE__, level, __VA_ARGS__); \
        } while(0)

void logger_routine( const char * func, char * file, int line, int level, const char *, ... );

void gsimavr_avr_logger( const int, const char *, va_list );

int app_verbosity;

#endif
