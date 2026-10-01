#include "kernel.h"
#include "registers.h"

void kernel_main(void)
{

    uint64_t clock_frequency = read_register_timer(REG_CNTFRQ); //in Hz. This is how much ticks need to pass for a secound.

    uart_puts("\n");
    uart_puts("===========================\n");
    uart_puts("  Onix: Hello from EL1!\n");
    uart_puts("===========================\n");
    uart_puts("\n");
    uart_puts("Clock frequency: %u Hz \n", clock_frequency);

    write_register_timer(REG_CNTP_TVAL, clock_frequency); //Set the timer to trigger an interrupt in 1 second
    write_register_timer(REG_CNTP_CTL, 1); //Enable the timer

    for (;;)
    {
        if (read_register_timer(REG_CNTP_CTL) & (1 << 2)) //Check if the timer is enabled
        {
            uart_puts("Time: %u\n", read_register_timer(REG_CNTFRQ) /read_register_timer(REG_CNTPCT));
        }
    }
   
}

//not working, check this code and also register.c; Might be cuz of the way read is set up...