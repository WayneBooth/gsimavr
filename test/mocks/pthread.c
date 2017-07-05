#include <pthread.h>
#include "../../src/logger.h"

extern int pthread_create (pthread_t *__restrict __newthread, const pthread_attr_t *__restrict __attr, void *(*__start_routine) (void *), void *__restrict __arg) {
  LOG( LOGGER_WARNING, "Simulatoring 'pthread_create'\n" );
  return 1;
}

extern int pthread_detach (pthread_t __th) {
  LOG( LOGGER_WARNING, "Simulatoring 'pthread_detach'\n" );
  return 1;
}

