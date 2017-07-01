
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h> 

#include "logger.h"
#include "model.h"
#include "sim_elf.h"
#include "sim_gdb.h"

void *lib;
typedef void (*ConfigureDevice)(void);
typedef int(*Core_reg_pin_to_location)(char *, int);

Core_reg_pin_to_location core_reg_pin_to_location;

uint32_t noConnection= 0b1111111111111111111111111111;
uint32_t powerPins  =  0b0000000000000000000000000000;
uint32_t powerState =  0b0000000000000000000000000000;

uint32_t ddrPins =     0b0000000000000000000000000000; // 1=output 0=input
uint32_t outputState = 0b0000000000000000000000000000;
uint32_t inputState =  0b0000000000000000000000000000;

int reg_pin_to_location ( char * reg, int pin ) {
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
	return ~noConnection & powerPins & powerState;
}

uint32_t get_negative_power() {
	return ~noConnection & powerPins & ~powerState;
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

void createAvr( char *firmwareName, char *firmwareMcu ) {

  int len = snprintf(NULL, 0, "../%s.elf", firmwareName );
  char *st = (char *)malloc(len+1);
  snprintf(st, len+1, "../%s.elf", firmwareName );
  LOG( LOGGER_DEBUG, "Loading firmware: %s\n", st);
  elf_firmware_t f;
  elf_read_firmware ( st, &f );
  free(st);

  avr_logger_p logger = (avr_logger_p)gsimavr_avr_logger;
  avr_global_logger_set( logger );

  LOG( LOGGER_DEBUG, "Generating AVR of type %s\n", firmwareMcu );
  avr = avr_make_mcu_by_name ( firmwareMcu );

  avr_init ( avr );

  avr->log = LOG_TRACE;
  avr_global_logger_set( logger );

  avr_load_firmware ( avr, &f );
  avr->frequency = 8000000UL;
}

int loadGsimavrCore( char *coreName ) {

  int len = snprintf(NULL, 0, "./cores/%s.so", coreName );
  char *st = (char *)malloc(len+1);
  snprintf(st, len+1, "./cores/%s.so", coreName );
  lib = dlopen( st, RTLD_NOW );
  if(lib == NULL) {
    LOG( LOGGER_ERROR, "ERROR: The core '%s' is not supported : %s\n", coreName, dlerror() );
    free(st);
    return 1;
  }
  free(st);
  LOG( LOGGER_ERROR, "Loaded core '%s'\n", coreName );

  ConfigureDevice configureDevice = dlsym(lib, "configureDevice");
  configureDevice();

  CHIPNAME  = dlsym (lib, "get_chipname");
  PINS =     (int)voidPtr_to_int( dlsym (lib, "core_pins") );
  REGISTERS = dlsym (lib, "get_registers");

  noConnection = voidPtr_to_int( dlsym (lib, "core_noConnection") );
  powerPins  =   voidPtr_to_int( dlsym (lib, "core_powerPins") );
  powerState =   voidPtr_to_int( dlsym (lib, "core_powerState") );

  ddrPins =      voidPtr_to_int( dlsym (lib, "core_ddrPins") );
  outputState =  voidPtr_to_int( dlsym (lib, "core_outputState") );
  inputState =   voidPtr_to_int( dlsym (lib, "core_inputState") );

  core_reg_pin_to_location = dlsym(lib, "core_reg_pin_to_location");

  LOG( LOGGER_DEBUG, "We have a %d pin %s, containing registers(%s)\n", PINS, CHIPNAME(), REGISTERS() );
  return 0;
}

void unloadCore() {

  dlclose(lib);

  core_reg_pin_to_location = NULL;

  PINS = 2;

  noConnection= 0b1111111111111111111111111111;
  powerPins  =  0b0000000000000000000000000000;
  powerState =  0b0000000000000000000000000000;

  ddrPins =     0b0000000000000000000000000000; // 1=output 0=input
  outputState = 0b0000000000000000000000000000;
  inputState =  0b0000000000000000000000000000;
}

void setupGdb( int waitForGdb ) {

  ////////////////////////////////
  // GDB setup
  if( waitForGdb == 1 ) {
    LOG( LOGGER_WARNING, "Connect GD to localhost:1234\n");
    avr->gdb_port = 1234;
    avr->state = cpu_Stopped;
    avr_gdb_init(avr);
  }

}

int setupSimulator( int waitForGdb ) {

  createAvr( WRAPPEDFIRMWARENAME, WRAPPEDFIRMWAREMCU );

  setupGdb( waitForGdb );

  ////////////////////////////////
  // VCD Setup

  return loadGsimavrCore( WRAPPEDFIRMWAREMCU );
}

