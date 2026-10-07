#include "registers.h"
#include "kernel.h"
#include "platform.h"

void irq_handler(void)
{
    
    uint32_t interrupt_id = GICC_IAR & 0x3FF; // Get the interrupt ID from the IAR register

    if(interrupt_id == TIMER_INTERRUPT_ID) 
    {
        // Handle the timer interrupt
        uart_puts("Time elapsed: %u seconds\n", read_register_timer(REG_CNTPCT) / read_register_timer(REG_CNTFRQ));
        
        // Reset the timer for the next interrupt
        uint64_t clock_frequency = read_register_timer(REG_CNTFRQ);
        write_register_timer(REG_CNTP_TVAL, clock_frequency); // Set the timer to trigger an interrupt in 1 second
    }

    GICC_EOIR = interrupt_id; // Signal end of interrupt to the GIC
}