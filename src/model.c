#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "model.h"
#include "sim_elf.h"
#include "sim_gdb.h"

#define WRAP2(X) #X
#define WRAP1(X) WRAP2(X)
#define WRAP(X) WRAP1(X)
 
#define WRAPPEDFIRMWAREMCU WRAP(FIRMWAREMCU)
#define WRAPPEDFIRMWARENAME WRAP(FIRMWARENAME)

uint32_t noConnection= 0b0000000100000000000000000001;
uint32_t powerPins  =  0b0000001010000000000011000000;
uint32_t powerState =  0b0000000010000000000001000000;

uint32_t ddrPins =     0b1111110101111111111100111110; // 1=output 0=input
uint32_t outputState = 0b0000000000000000000000000000;
uint32_t inputState =  0b0000000000000000000000000000;

int reg_pin_to_location ( char * reg, int pin ) {
  if( strcmp( "B", reg ) == 0 ) {
    switch(pin) {
      case 0:
        return 14;
      case 1:
        return 15;
      case 2:
        return 16;
      case 3:
        return 17;
      case 4:
        return 18;
      case 5:
        return 19;
      case 6:
        return 9;
      case 7:
        return 10;
      default:
        return 0;
    }
  }
  if( strcmp( "C", reg ) == 0 ) {
    switch(pin) {
      case 0:
        return 23;
      case 1:
        return 24;
      case 2:
        return 25;
      case 3:
        return 26;
      case 4:
        return 27;
      case 5:
        return 28;
      case 6:
        return 1;
      default:
        return 0;
    }
  }
  if( strcmp( "D", reg ) == 0 ) {
    switch(pin) {
      case 0:
        return 2;
      case 1:
        return 3;
      case 2:
        return 4;
      case 3:
        return 5;
      case 4:
        return 6;
      case 5:
        return 11;
      case 6:
        return 12;
      case 7:
        return 13;
      default:
        return 0;
    }
  }

  return 0;
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

void setupSimulator( int waitForGdb ) {


  int len = snprintf(NULL, 0, "../%s.elf", WRAPPEDFIRMWARENAME);
  char *st = (char *)malloc(len+1);
  snprintf(st, len+1, "../%s.elf", WRAPPEDFIRMWARENAME);

  elf_firmware_t f;
  elf_read_firmware ( st, &f );

  free(st);



  avr = avr_make_mcu_by_name ( WRAPPEDFIRMWAREMCU );
  avr_init ( avr );
  avr_load_firmware ( avr, &f );
  avr->frequency = 8000000UL;


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

}

