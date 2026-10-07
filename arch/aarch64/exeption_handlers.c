#include "registers.h"
#include "kernel.h"

void irq_handler()
{
    read_register_timer(REG_CNTP_CTL); //Read the control register to clear the interrupt
    write_register_timer(REG_CNTP_TVAL, read_register_timer(REG_CNTFRQ)); //Set the timer to trigger an interrupt in 1 second
    write_register_timer(REG_CNTP_CTL, 1); //Enable the timer
    uart_puts("Time: %u\n", read_register_timer(REG_CNTFRQ) / read_register_timer(REG_CNTPCT)); //Print the time in seconds
}