
#ifndef ___LOGGER_H___
#define ___LOGGER_H___

#include <stdarg.h>

enum {
        LOGGER_NONE = 0,
        LOGGER_OUTPUT,
        LOGGER_ERROR,
        LOGGER_WARNING,
        LOGGER_TRACE,
        LOGGER_DEBUG,
};

typedef void (*logger_p)(const int level, const char * format, va_list ap);

#define LOG(level, ...) \
        do { \
                logger_routine(level, __VA_ARGS__); \
        } while(0)

void logger_routine( const int, const char *, ... );

int app_verbosity;

#endif
