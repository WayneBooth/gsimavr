#include <sim_avr.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

avr_t * avr_make_mcu_by_name( const char *name) {
	printf("Simulating 'avr_make_mcu_by_name'\n");
	return (avr_t *)malloc(sizeof(avr_t));
}

int avr_init( avr_t * avr ) {
	printf("Simulating 'avr_init'\n");
	return 0;	
}

struct avr_irq_t * avr_io_getirq( avr_t * avr, uint32_t ctl, int index) {
	printf("Simulating 'avr_io_getirq' with port '%c'\n", ctl);
	return 0;
}

void avr_connect_irq( avr_irq_t * src, avr_irq_t * dst) {
	printf("Simulating 'avr_connect_irq'\n");
}

void avr_unconnect_irq( avr_irq_t * src, avr_irq_t * dst) {
	printf("Simulating 'avr_unconnect_irq'\n");
}

void avr_irq_register_notify( avr_irq_t * irq, avr_irq_notify_t notify, void * param) {
	printf("Simulating 'avr_irq_register_notify' with port '%s'\n", (char *)param);
}

void avr_raise_irq( avr_irq_t * irq, uint32_t value) {
	printf("Simulating 'avr_raise_irq'\n");
}

int avr_run( avr_t * avr) {
	printf("Simulating 'avr_run'\n");
	return 0;	
}

avr_irq_t * avr_alloc_irq( avr_irq_pool_t * pool, uint32_t base, uint32_t count, const char ** names /* optional */) {
	printf("Simulating 'avr_alloc_irq'\n");
	return NULL;
}

void avr_cycle_timer_register_usec( struct avr_t * avr, uint32_t when, avr_cycle_timer_t timer, void * param) {
	printf("Simulating 'avr_cycle_timer_register_usec'\n");
	timer( avr, when, param );
}

int avr_gdb_init(avr_t * avr) {
	printf("Simulating 'avr_gdb_init'\n");
	return 0;
}

void avr_global_logger_set( avr_logger_p logger ) {
	printf("Simulating 'avr_global_logger_set'\n");
}

void gsimavr_avr_logger( const int, const char *, va_list );

void avr_global_logger( struct avr_t *avr, const int level, const char * format, ... ) {
	va_list args;
	va_start(args, format);
	gsimavr_avr_logger( level, format, args );
	va_end(args);
}
