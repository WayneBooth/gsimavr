#include <string.h>

#include "core.h"
#include "../model.h"

void configureDevice() {

  core_chipname = "ATtiny2313";
  core_pins = 20;
  core_registers = "ABD";

  core_noConnection = 0b0000000000000000000000000001;
  core_powerPins  =   0b0000000010000000001000000000;
  core_powerState =   0b0000000010000000000000000000;

  core_ddrPins =      0b0000000001111111110111111110; // 1=output 0=input
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
  if( strcmp( "A", reg ) == 0 ) {
    switch(pin) {
      case 0:
        return 5;
      case 1:
        return 4;
      case 2:
        return 1;
      case 3:
        return 0;
      case 4:
        return 0;
      case 5:
        return 0;
      case 6:
        return 0;
      default:
        return 0;
    }
  }
  if( strcmp( "B", reg ) == 0 ) {
    switch(pin) {
      case 0:
        return 12;
      case 1:
        return 13;
      case 2:
        return 14;
      case 3:
        return 15;
      case 4:
        return 16;
      case 5:
        return 17;
      case 6:
        return 18;
      case 7:
        return 19;
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
        return 6;
      case 3:
        return 7;
      case 4:
        return 8;
      case 5:
        return 9;
      default:
        return 0;
    }
  }

  return 0;
}

