# gsimavr-example

Example use for the [gsimavr](https://github.com/WayneBooth/gsimavr) project

## How to use

* Clone this repository.
* Check your dependencies (see the gsimavr project).
* (optional) Update the makefile to specify the *MCU*, the firmware will correctly build for atmega328p and attiny2313 targets.
* run ```make```, to build the avr firmware.
* enter the 'gui' directory and run ```make```. This will compile and start the gui app.
  * The app will load the firmware from the parent directory as defined in the makefile *PROJECTNAME* and *MCU* variable.
  * The app will automatically configure input/output pins as defined by the firmware.
* How to use the gui:
  * Left click on an input to turn it on,
  * Right click on an input to turn it off,
  * Middle click on an input to connect it to a clock signal

