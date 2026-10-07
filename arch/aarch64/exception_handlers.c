#include "registers.h"
#include "kernel.h"

void irq_handler()
{
    uart_puts("Time: %u\n", read_register_timer(REG_CNTFRQ) / read_register_timer(REG_CNTPCT)); //Print the time in seconds
    write_register_timer(REG_CNTP_TVAL, read_register_timer(REG_CNTFRQ)); //Set the timer to trigger an interrupt in 1 second
}