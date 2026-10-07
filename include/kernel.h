#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "registers.h"

void uart_putc(char c);
void uart_puts(const char *s, ...);
char uart_getc(void);
char *itoa(int value);
void uart_puthex(unsigned long n);

void gic_init(void);
void gic_enable_interrupt(uint32_t interrupt_id);
void gic_disable_interrupt(uint32_t interrupt_id);

void kernel_main(void);

#endif