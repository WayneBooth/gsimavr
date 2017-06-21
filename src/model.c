
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h> 

#include "model.h"
#include "sim_elf.h"
#include "sim_gdb.h"

void *lib;
typedef void (*ConfigureDevice)(void);
typedef int(*Core_reg_pin_to_location)(char *, int);

uint32_t noConnection= 0b1111111111111111111111111111;
uint32_t powerPins  =  0b0000000000000000000000000000;
uint32_t powerState =  0b0000000000000000000000000000;

uint32_t ddrPins =     0b0000000000000000000000000000; // 1=output 0=input
uint32_t outputState = 0b0000000000000000000000000000;
uint32_t inputState =  0b0000000000000000000000000000;

int reg_pin_to_location ( char * reg, int pin ) {
	Core_reg_pin_to_location core_reg_pin_to_location = dlsym(lib, "core_reg_pin_to_location");
	return core_reg_pin_to_location( reg, pin );
}

void set_state( uint32_t *reg, int pin, int isOn ) {
	if( isOn ) {
		*reg |= ( 1 << (pin-1) );
	}
	else {
		*reg &= ~( 1 << (pin-1) );
	}
}

void set_ddr( int pin, int ddr ) {
	set_state( &ddrPins, pin, ddr );
}

void set_outputState( int pin, int isOutputOn ) {
	set_state( &outputState, pin, isOutputOn );
}

void set_inputState( int pin, int isInputOn ) {
	set_state( &inputState, pin, isInputOn );
}

void set_ioState( int pin, int ddr ) {
	if( ddrPins & ( 1 << (pin-1) ) ) {
		set_outputState( pin, ddr );
	}
	else {
		set_inputState( pin, ddr );
	}
}

uint32_t get_positive_power() {
	return powerPins & powerState;
}

uint32_t get_negative_power() {
	return powerPins & ~powerState;
}

uint32_t get_positive_outputs() {
	return ~noConnection & ~powerPins & ddrPins & outputState;
}

uint32_t get_negative_outputs() {
	return ~noConnection & ~powerPins & ddrPins & ~outputState;
}

uint32_t get_positive_inputs() {
	return ~noConnection & ~powerPins & ~ddrPins & inputState;
}

uint32_t get_negative_inputs() {
	return ~noConnection & ~powerPins & ~ddrPins & ~inputState;
}

uint32_t voidPtr_to_int( void * ptr ) {
  uint32_t *ptr_ptr = ptr;
  return *ptr_ptr;
}

int setupSimulator( int waitForGdb ) {


  int len = snprintf(NULL, 0, "../%s.elf", WRAPPEDFIRMWARENAME);
  char *st = (char *)malloc(len+1);
  snprintf(st, len+1, "../%s.elf", WRAPPEDFIRMWARENAME);
  elf_firmware_t f;
  elf_read_firmware ( st, &f );
  free(st);



  len = snprintf(NULL, 0, "./cores/%s.so", WRAPPEDFIRMWAREMCU );
  st = (char *)malloc(len+1);
  snprintf(st, len+1, "./cores/%s.so", WRAPPEDFIRMWAREMCU );
  lib = dlopen( st, RTLD_NOW );
  if(lib == NULL) {
    printf("ERROR: The core '%s' is not supported : %s\n", WRAPPEDFIRMWAREMCU, dlerror() );
    free(st);
    return 1;
  }
  free(st);



  avr = avr_make_mcu_by_name ( WRAPPEDFIRMWAREMCU );
  avr_init ( avr );
  avr_load_firmware ( avr, &f );
  avr->frequency = 8000000UL;



  ConfigureDevice configureDevice = dlsym(lib, "configureDevice");
  configureDevice();

  PINS =    (int)voidPtr_to_int( dlsym (lib, "core_pins") );

  noConnection = voidPtr_to_int( dlsym (lib, "core_noConnection") );
  powerPins  =   voidPtr_to_int( dlsym (lib, "core_powerPins") );
  powerState =   voidPtr_to_int( dlsym (lib, "core_powerState") );

  ddrPins =      voidPtr_to_int( dlsym (lib, "core_ddrPins") );
  outputState =  voidPtr_to_int( dlsym (lib, "core_outputState") );
  inputState =   voidPtr_to_int( dlsym (lib, "core_inputState") );

  printf("We have %d PINS\n", PINS );
//  dlclose(lib);



  ////////////////////////////////
  // GDB setup
  if( waitForGdb == 1 ) {
    printf("Connect GD to localhost:1234\n");
    avr->gdb_port = 1234;
    avr->state = cpu_Stopped;
    avr_gdb_init(avr);
  }

  ////////////////////////////////
  // VCD Setup

  return 0;
}

