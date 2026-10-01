#include "registers.h"
#include "stdint.h"


uint64_t read_register_timer(uint16_t reg) 
{
    uint64_t value = 0;

    switch (reg) {
        case REG_CNTFRQ:
            asm volatile("mrs %0, cntfrq_el0" : "=r" (value));
            break;
        case REG_CNTPCT:
            asm volatile("mrs %0, cntpct_el0" : "=r" (value));
            break;
        case REG_CNTP_TVAL:
            asm volatile("mrs %0, cntp_tval_el0" : "=r" (value));
            break;
        case REG_CNTP_CVAL:
            asm volatile("mrs %0, cntp_cval_el0" : "=r" (value));
            break;
        case REG_CNTP_CTL:
            asm volatile("mrs %0, cntp_ctl_el0" : "=r" (value));
            break;
        case REG_CNTV_TVAL:
            asm volatile("mrs %0, cntv_tval_el0" : "=r" (value));
            break;
        case REG_CNTV_CVAL:
            asm volatile("mrs %0, cntv_cval_el0" : "=r" (value));
            break;
        case REG_CNTV_CTL:
            asm volatile("mrs %0, cntv_ctl_el0" : "=r" (value));
            break;
        default:
            // Erro ou registo inválido
            value = 0;
            break;
    }

    return value;
}

uint64_t write_register_timer(uint16_t reg, uint64_t value) 
{
    switch (reg) {
        case REG_CNTFRQ:
            return -1;
            break;
        case REG_CNTPCT:
            return -2;
            break;
        case REG_CNTP_TVAL:
            asm volatile("msr cntp_tval_el0, %0" : : "r" (value));
            break;
        case REG_CNTP_CVAL:
            asm volatile("msr cntp_cval_el0, %0" : : "r" (value));
            break;
        case REG_CNTP_CTL:
            asm volatile("msr cntp_ctl_el0, %0" : : "r" (value));
            break;
        case REG_CNTV_TVAL:
            asm volatile("msr cntv_tval_el0, %0" : : "r" (value));
            break;
        case REG_CNTV_CVAL:
            asm volatile("msr cntv_cval_el0, %0" : : "r" (value));
            break;
        case REG_CNTV_CTL:
            asm volatile("msr cntv_ctl_el0, %0" : : "r" (value));
            break;
        default:
            // Erro ou registo inválido
            value = 0;
            break;
    }

    return value;
}

