#include <sim_elf.h>
#include <stdio.h>

int elf_read_firmware(const char * file, elf_firmware_t * firmware){
	printf("Simulating 'elf_read_firmware'\n");
	return 1;
}

void avr_load_firmware(avr_t * avr, elf_firmware_t * firmware) {
	printf("Simulating 'avr_load_firmware'\n");
}
