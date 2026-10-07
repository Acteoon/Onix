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

    gic_init(); //Initialize the GIC and enable the timer interrupt
    asm volatile ("msr daifclr, #2" ::: "memory"); //Enable IRQs by clearing the I bit in the DAIF register -->
    for(;;) {
        // Wait for interrupts
    }
   
}