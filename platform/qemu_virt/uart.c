#include "platform.h"
#include "kernel.h"
#include "stdarg.h"
#include "stdint.h"

void uart_putc(char c)
{
    while (UART_FR & FR_TXFF) //Verifica (espera) se o UART nao esta full txff
        ;
    UART_DR = c; //poe o char no Data Reciver para enviar
}

void uart_puts(const char *s, ...)
{
    va_list args;
    uint16_t i = 0;
    va_start(args, s);

    while (*s) {
        if (*s == '%')
        {
            s++;
            switch (*s)
            {
                case 's':
                    uart_puts(va_arg(args, char *));
                    *s++;
                    break;
                case 'd':
                    uart_puts(itoa(va_arg(args, int)));
                    *s++;
                    break;
                case 'u':
                    uart_puts(itoa(va_arg(args, unsigned int)));
                    *s++;
                    break;
                case 'x':
                    uart_puthex(va_arg(args, unsigned long));
                    *s++;
                    break;
                case 'c':
                    uart_putc(va_arg(args, int));
                    *s++;
                    break;
                default:
                    uart_putc('%');
                    uart_putc(*s);
                    *s++;
                    break;
            }
            continue;
        }
            
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++); //puts current s and then increments the pointer to the next char
    }

    va_end(args);
}

char uart_getc(void)
{
    while (UART_FR & FR_RXFE)
        ;
    return UART_DR;
}

char *itoa(int value)
{
    static char buffer[12]; // Buffer to hold the string representation of the integer
    char *ptr = &buffer[11]; // Start from the end of the buffer
    *ptr = '\0'; // Null-terminate the string

    if (value == 0) {
        *--ptr = '0'; // Handle zero case
        return ptr;
    }

    int is_negative = 0;
    if (value < 0) {
        is_negative = 1; // Mark as negative
        value = -value; // Make value positive for conversion
    }

    while (value > 0) {
        *--ptr = '0' + (value % 10); // Get the last digit and convert to character
        value /= 10; // Remove the last digit
    }

    if (is_negative) {
        *--ptr = '-'; // Add negative sign if needed
    }

    return ptr; // Return pointer to the start of the string
}

void uart_puthex(unsigned long n)
{
    char hex[] = "0123456789abcdef";
    int i;
    uart_puts("0x");
    for (i = 60; i >= 0; i -= 4)
        uart_putc(hex[(n >> i) & 0xF]);
}