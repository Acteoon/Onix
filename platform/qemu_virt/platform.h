#ifndef PLATFORM_H
#define PLATFORM_H

#define UART_BASE       0x09000000

#define UART_DR         (*(volatile unsigned int *)(UART_BASE + 0x000))
#define UART_FR         (*(volatile unsigned int *)(UART_BASE + 0x018))

#define FR_TXFF         (1 << 5)
#define FR_RXFE         (1 << 4)

#define TIMER_INTERRUPT_ID 30U

#define GICD_BASE       0x08000000
#define GICC_BASE       0x08010000

#define GICC_CTLR       (*(volatile unsigned int *)(GICC_BASE + 0x000)) // CPU Interface Control Register
#define GICC_PMR        (*(volatile unsigned int *)(GICC_BASE + 0x004)) // Interrupt Priority Mask Register
#define GICC_IAR        (*(volatile unsigned int *)(GICC_BASE + 0x00C)) // Interrupt Acknowledge Register
#define GICC_EOIR       (*(volatile unsigned int *)(GICC_BASE + 0x010)) // End of Interrupt Register

#define GICD_CTLR       (*(volatile unsigned int *)(GICD_BASE + 0x000)) // Distributor Control Register
#define GICD_ISENABLER  ((volatile unsigned int *)(GICD_BASE + 0x100)) // Interrupt Set-Enable Registers
#define GICD_ICENABLER  ((volatile unsigned int *)(GICD_BASE + 0x180)) // Interrupt Clear-Enable Registers
#define GICD_IPRIORITYR_BYTES ((volatile unsigned char *)(GICD_BASE + 0x400)) // Interrupt Priority Registers
#define GICD_ITARGETSR (*(volatile unsigned int *)(GICD_BASE + 0x800)) // Interrupt Processor Targets Registers


#endif