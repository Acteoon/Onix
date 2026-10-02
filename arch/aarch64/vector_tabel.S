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
    b irq_handler_entry

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