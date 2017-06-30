#include <pthread.h>

extern int pthread_create (pthread_t *__restrict __newthread, const pthread_attr_t *__restrict __attr, void *(*__start_routine) (void *), void *__restrict __arg) {
  return 1;
}

extern int pthread_detach (pthread_t __th) {
  return 1;
}

