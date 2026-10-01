#ifndef PLATFORM_H
#define PLATFORM_H

#define UART_BASE       0x09000000

#define UART_DR         (*(volatile unsigned int *)(UART_BASE + 0x000))
#define UART_FR         (*(volatile unsigned int *)(UART_BASE + 0x018))

#define FR_TXFF         (1 << 5)
#define FR_RXFE         (1 << 4)

#endif