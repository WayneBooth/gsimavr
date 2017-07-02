#ifndef __CORE_H__
#define __CORE_H__

#include <stdint.h>

char * core_chipname;
int core_pins;
char * core_registers;

uint32_t core_noConnection;
uint32_t core_powerPins;
uint32_t core_powerState;

uint32_t core_ddrPins;
uint32_t core_outputState;
uint32_t core_inputState;

void configureDevice();
char *get_registers();
char *get_chipname();
int core_reg_pin_to_location ( char *, int );

#endif
