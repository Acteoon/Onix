#include <stdint.h>

#define REG_CNTFRQ 0U // Frequency register. What is the frequency of the timer in Hz. This is how many ticks need to pass for a second.
#define REG_CNTPCT 1U // Physical count register. This register contains the current value of the physical counter.
#define REG_CNTP_TVAL 2U // Timer value register. This register contains the value that the timer will count down from. When the timer reaches zero, it will trigger an interrupt.
#define REG_CNTP_CVAL 3U // Timer compare value register. This register contains the value that the timer will compare against. When the timer reaches this value, it will trigger an interrupt.
#define REG_CNTP_CTL 4U // Timer control register. This register contains the control bits for the timer. It is used to enable or disable the timer, and to set the timer mode (one-shot or periodic). The bits in this register are: 0 for ENABLE, 1 for IMASK, and 2 for ISTATUS.
           /* Bit 0	ENABLE	Enables or disables the physical timer. 
            • 1: Timer enabled.
            • 0: Timer disabled (stops output signal but physical counter keeps incrementing).
            Bit 1	IMASK	Interrupt Mask bit. 
            • 1: Masks (mutes) the timer's interrupt output.
            • 0: Allows the timer to trigger a hardware interrupt when the time expires.
            Bit 2	ISTATUS	Interrupt Status bit (Read-Only). 
            • 1: Timer condition met (time has expired).
            • 0: Timer condition not met. */
        
        //Virtual timers
#define REG_CNTV_TVAL 5U // Virtual timer value register. This register contains the value that the virtual timer will count down from. When the virtual timer reaches zero, it will trigger an interrupt.
#define REG_CNTV_CVAL 6U // Virtual timer compare value register. This register contains the value that the virtual timer will compare against. When the virtual timer reaches this value, it will trigger an interrupt.
#define REG_CNTV_CTL 7U // Virtual timer control register. This register contains the control bits for the virtual timer. It is used to enable or disable the virtual timer, and to set the virtual timer mode (one-shot or periodic).
#define REG_TIMER_COUNT 8U // Timer count register. This register contains the current value of the timer.


uint64_t read_register_timer(uint16_t reg);
uint64_t write_register_timer(uint16_t reg, uint64_t value);

