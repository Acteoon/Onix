#include <stdint.h>
#include "registers.h"

void uart_putc(char c);
void uart_puts(const char *s, ...);
char uart_getc(void);
char *itoa(int value);
void uart_puthex(unsigned long n);

void kernel_main(void);