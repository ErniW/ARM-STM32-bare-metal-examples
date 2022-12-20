#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"
#include "pll.h"

volatile uint32_t ms_counter = 0;
volatile uint32_t millis = 0;

void SysTick_Init(){
    SysTick->VAL = 0;
    SysTick->LOAD = (HCLK_FREQ / 1000)- 1;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(){
    if (ms_counter) ms_counter--;
    millis++;
}

void delay_ms(uint32_t ms){
    ms_counter = ms;
    while (ms_counter);
}

uint32_t getMillis(){
    return millis;
}