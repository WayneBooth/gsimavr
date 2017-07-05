#include <sim_elf.h>
#include <stdio.h>
#include "../../src/logger.h"

int elf_read_firmware(const char * file, elf_firmware_t * firmware){
	LOG( LOGGER_WARNING, "Simulating 'elf_read_firmware'\n" );
	return 1;
}

void avr_load_firmware(avr_t * avr, elf_firmware_t * firmware) {
	LOG( LOGGER_WARNING, "Simulating 'avr_load_firmware'\n" );
}
