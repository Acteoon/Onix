#include "platform.h"
#include "stdint.h"
#include "kernel.h"

void gic_init(void)
{
    // Enable the GIC Distributor
    GICD_CTLR = 1;

    // Enable the GIC CPU Interface
    GICC_CTLR = 1;

    GICC_PMR = 0xFF; // Set priority mask to allow all priorities
    
    GICD_IPRIORITYR_BYTES[TIMER_INTERRUPT_ID] = 0x00; // Set the priority of the timer interrupt to a lower value (higher priority)

    gic_enable_interrupt(TIMER_INTERRUPT_ID); // Enable the timer interrupt
}

void gic_enable_interrupt(uint32_t interrupt_id)
{
     //example: interrupt_id = 30
    uint32_t reg_index = interrupt_id / 32; //30 / 32 = 0 so reg_index = 0
    uint32_t bit_position = interrupt_id % 32; //30 % 32 = 30 so bit_position = 30
    uint32_t bit_mask = 1U << bit_position; // 1U << 30 = 0x40000000 make it a bitmask to enable the interrupt
    GICD_ISENABLER[reg_index] = bit_mask; // Enable the specified interrupt in the distributor
}

void gic_disable_interrupt(uint32_t interrupt_id)
{
    uint32_t reg_index = interrupt_id / 32;
    uint32_t bit_position = interrupt_id % 32;
    uint32_t bit_mask = 1U << bit_position;
    GICD_ICENABLER[reg_index] = bit_mask; // Disable the specified interrupt in the distributor
}