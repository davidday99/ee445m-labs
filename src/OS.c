// OS.c
// Runs on TM4C123
// OS functions 
// David Day 
// Jan 3, 2022 

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "OS.h"

#define NVIC_EN0_INT15 0x8000
#define SYSTICK_RELOAD 79      // 1 us period for 80 MHz system clock

static uint32_t SysTimeMicroSeconds;

static void InitDebug(void) {
    SYSCTL_RCGCGPIO_R |= 2;
    GPIO_PORTB_DEN_R |= 8;
    GPIO_PORTB_DIR_R |= 8;
}

void OS_InitSysTime(void) {
    NVIC_ST_CTRL_R &= 0x7;  // clear SysTick control register
    NVIC_ST_RELOAD_R &= 0x00FFFFFF;
    NVIC_ST_RELOAD_R = SYSTICK_RELOAD;
    NVIC_EN0_R |= NVIC_EN0_INT15;  // enable SysTick interrupt in NVIC
    NVIC_ST_CTRL_R |= 7;  // enable clock with interrupts, clk src is sys clock

    InitDebug();
}

void SysTick_Handler(void) {
    GPIO_PORTB_DATA_R |= 8;
    SysTimeMicroSeconds++;
    GPIO_PORTB_DATA_R &= ~8;
}

void OS_ClearPeriodicTime(void) {
    SysTimeMicroSeconds = 0;
}

uint32_t OS_ReadPeriodicTime(void) {
    return SysTimeMicroSeconds;
}

int OS_AddPeriodicThread(void (*task)(void), uint32_t period, uint32_t priority) {
    return 1;
}
