
#ifndef __UTILS_H__
#define __UTILS_H__

#include "../src/logger.h"

extern logger_p _logger_routine;

void start_capturing_log( logger_p logger );
void start_capturing_log_std();
void stop_capturing_log();

char *get_log_contents();

#endif
