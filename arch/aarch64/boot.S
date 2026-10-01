.section ".text.boot", "ax"      // Put this code in the boot section
.globl _start                     // Make _start globally visible to the linker
_start:                           // Kernel entry point on reset
    mrs     x0, CurrentEL         // Read the current exception level into x0
    and     x0, x0, #0xC          // Mask bits 2:3 to isolate the EL value
    lsr     x0, x0, #2            // Shift down so EL3=3, EL2=2, EL1=1, EL0=0

    cmp     x0, #3                // If we are at EL3, jump to the EL3 setup path
    bne     el2_entry             // Otherwise, skip EL3 init and continue to EL2 check

    mov     x0, #0x30             // Set SCR_EL3 bits: enable NS and HCE (EL2 access)
    msr     scr_el3, x0           // Write the secure configuration register for EL3
    mov     x0, #0x3C9            // Set SPSR_EL3: EL2, interrupt mask bits, and execution state
    msr     spsr_el3, x0          // Save the next CPU state for the ERET to EL2
    adr     x0, el2_entry         // Load the address of the EL2 entry label
    msr     elr_el3, x0           // Set ELR_EL3 so ERET returns to el2_entry
    eret                         // Return to EL2 with the configured SPSR/SCR state

el2_entry:                        // Entry point after leaving EL3, if present
    cmp     x0, #2                // If we are at EL2, set up EL2 state
    bne     el1_entry             // Otherwise, continue directly to EL1 setup

    mov     x0, #(1 << 31)        // Set HCR_EL2.TGE bit to enable a 64-bit guest/EL1 environment
    msr     hcr_el2, x0           // Write the Hypervisor Configuration Register
    mov     x0, #0x3C5            // Set SPSR_EL2: EL1, interrupts masked, execution state bits
    msr     spsr_el2, x0          // Save the EL1 state for later ERET
    adr     x0, el1_entry         // Load the address of the EL1 entry label
    msr     elr_el2, x0           // Set ELR_EL2 so ERET jumps to EL1 code
    eret                         // Return to EL1

el1_entry:                        // Final privilege level before C kernel entry
    ldr     x0, =__stack_top      // Load the top of the temporary stack
    mov     sp, x0                // Set the stack pointer for the kernel

    ldr     x0, =__bss_start      // Load the start of the .bss section
    ldr     x1, =__bss_end        // Load the end of the .bss section
    mov     x2, #0                // Set x2 to zero for BSS initialization
1:  str     x2, [x0], #8          // Store zero into one word at a time, then advance x0 by 8 bytes
    cmp     x0, x1                // Compare current pointer with the end address
    b.lo    1b                   // If x0 < x1, repeat until BSS is zeroed

    bl      kernel_main           // Call the C kernel entry point

2:  wfe                          // Wait for event; low-power idle loop while the kernel runs
    b       2b                   // Loop forever if the kernel ever returns