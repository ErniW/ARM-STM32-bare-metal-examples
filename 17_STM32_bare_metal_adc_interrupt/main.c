#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdio.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    tx_init();
    adc_init();
    adc_int_init();

    adc_start_conversion();

    while(1){

    };
}

int __io_putchar(int ch){
    tx_send(ch);
    return ch;
}