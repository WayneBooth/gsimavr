#include <string.h>

#include "core.h"
#include "../model.h"

void configureDevice() {

  core_chipname = "ATtiny13";
  core_pins = 8;
  core_registers = "B";

  core_noConnection = 0b00000001;
  core_powerPins  =   0b10001000;
  core_powerState =   0b10000000;

  core_ddrPins =      0b01110110; // 1=output 0=input
  core_outputState =  0b00000000;
  core_inputState =   0b00000000;
}

char *get_registers() {
  return core_registers;
}

char *get_chipname() {
  return core_chipname;
}

int core_reg_pin_to_location ( char reg, int pin ) {
  if( 'B' == reg ) {
    switch(pin) {
      case 0:
        return 5;
      case 1:
        return 6;
      case 2:
        return 7;
      case 3:
        return 2;
      case 4:
        return 3;
      case 5:
        return 1;
      default:
        return 0;
    }
  }

  return 0;
}

