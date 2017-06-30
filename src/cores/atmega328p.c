#include <string.h>

#include "../model.h"

char * core_chipname;
int core_pins;
char * core_registers;

uint32_t core_noConnection;
uint32_t core_powerPins;
uint32_t core_powerState;

uint32_t core_ddrPins;
uint32_t core_outputState;
uint32_t core_inputState;

void configureDevice() {

  core_chipname = "ATmega328P";
  core_pins = 28;
  core_registers = "BCD";

  core_noConnection = 0b0000000100000000000000000001;
  core_powerPins  =   0b0000001010000000000011000000;
  core_powerState =   0b0000000010000000000001000000;

  core_ddrPins =      0b1111110101111111111100111110; // 1=output 0=input
  core_outputState =  0b0000000000000000000000000000;
  core_inputState =   0b0000000000000000000000000000;
}

char *get_registers() {
  return core_registers;
}

char *get_chipname() {
  return core_chipname;
}

int core_reg_pin_to_location ( char * reg, int pin ) {
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

