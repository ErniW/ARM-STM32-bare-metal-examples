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
    adc_init_two();

    while(1){

        uint32_t value1 = adc_read_channel(0);
        delay_ms(20);
        uint32_t value2 = adc_read_channel(1);
        delay_ms(20);

        printf("%d, %d \n\r", (int)value1, (int)value2);
    };
}

int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}