#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdio.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

volatile uint16_t values[2];

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    tx_init();
    adc_dma_init();
    adc_dma_config((uint32_t)&ADC1->DR, (uint32_t)values, 2);
    
    while(1){
        printf("Values: %d, %d\n\r", (int)values[0], (int)values[1]);
    };
}

int __io_putchar(int ch){
    tx_send(ch);
    return ch;
}