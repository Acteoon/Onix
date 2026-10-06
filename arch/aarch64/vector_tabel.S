.section .text
.global vector_table

.align 11 // Align to 2^11 = 2048 bytes for vector table alignment
vector_table:

.align 7 // Align to 2^7 = 128 bytes for each vector entry
current_el_sp0_synchronous: //label, like a function 
    b stuck_forever //Goto stuck_forever

.align 7
current_el_sp0_irq:
    b stuck_forever //Goto stuck_forever

.align 7
current_el_sp0_fiq:
    b stuck_forever //Goto stuck_forever

.align 7
current_el_sp0_serror:
    b stuck_forever //Goto stuck_forever

.align 7
current_el_spx_synchronous:
    b stuck_forever //Goto stuck_forever

.align 7
current_el_spx_irq:
    stp x30, x18, [sp, #-16]! // Save link register and x18 to stack
    bl save_registers //save_registers
    bl irq_handler_entry //Goto irq_handler_entry
    bl restore_registers //restore_registers
    ldp x30, x18, [sp], #16 // Restore link register and x18
    eret // Return from exception

.align 7
current_el_spx_fiq:
    b stuck_forever //Goto stuck_forever

.align 7
current_el_spx_serror:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch64_synchronous:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch64_irq:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch64_fiq:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch64_serror:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch32_synchronous:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch32_irq:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch32_fiq:
    b stuck_forever //Goto stuck_forever

.align 7
lower_el_aarch32_serror:
    b stuck_forever //Goto stuck_forever

stuck_forever:
    b .

irq_handler_entry:
    b irq_handler //Goto irq_handler

save_registers:
    stp x0, x1, [sp, #-16]! // Save x0 and x1 to stack
    stp x2, x3, [sp, #-16]! // Save x2 and x3 to stack
    stp x4, x5, [sp, #-16]! // Save x4 and x5 to stack
    stp x6, x7, [sp, #-16]! // Save x6 and x7 to stack
    stp x8, x9, [sp, #-16]! // Save x8 and x9 to stack
    stp x10, x11, [sp, #-16]! // Save x10 and x11 to stack
    stp x12, x13, [sp, #-16]! // Save x12 and x13 to stack
    stp x14, x15, [sp, #-16]! // Save x14 and x15 to stack
    stp x16, x17, [sp, #-16]! // Save x16 and x17 to stack
    ret // Return from function

restore_registers:
    ldp x16, x17, [sp], #16 // Restore x16 and x17 from stack
    ldp x14, x15, [sp], #16 // Restore x14 and x15 from stack
    ldp x12, x13, [sp], #16 // Restore x12 and x13 from stack
    ldp x10, x11, [sp], #16 // Restore x10 and x11 from stack
    ldp x8, x9, [sp], #16 // Restore x8 and x9 from stack
    ldp x6, x7, [sp], #16 // Restore x6 and x7 from stack
    ldp x4, x5, [sp], #16 // Restore x4 and x5 from stack
    ldp x2, x3, [sp], #16 // Restore x2 and x3 from stack
    ldp x0, x1, [sp], #16 // Restore x0 and x1 from stack
    ret // Return from function