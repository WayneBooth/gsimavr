
#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdint.h>
#include <sim_avr.h>

#define WRAP2(X) #X
#define WRAP1(X) WRAP2(X)
#define WRAP(X) WRAP1(X)

#define WRAPPEDFIRMWAREMCU WRAP(FIRMWAREMCU)
#define WRAPPEDFIRMWARENAME WRAP(FIRMWARENAME)

avr_t * avr;

char *(*CHIPNAME)();
int PINS;

int reg_pin_to_location ( char *, int );
void set_ddr( int , int );
void set_ioState( int , int );
uint32_t get_positive_power();
uint32_t get_negative_power();
uint32_t get_positive_outputs();
uint32_t get_negative_outputs();
uint32_t get_positive_inputs();
uint32_t get_negative_inputs();
int setupSimulator( int );

#endif
