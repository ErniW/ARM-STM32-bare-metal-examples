#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

    tx_init();
    adc_init_two();

    //adc_start_conversion();

    while(1){

        uint32_t value1 = adc_read_value(0);
        // delay_ms(20);
        uint32_t value2 = adc_read_value(1);
        // delay_ms(20);

        printf("%d, %d \n\r", (int)value1, (int)value2);
        //printf("Sensor value : %d \n\r", (int)value2);

        // volatile uint32_t value = adc_read();
        // printf("Sensor value : %d \n\r", (int)value);
        // volatile uint32_t value2 = adc_read();
        // printf("Sensor value : %d \n\r", (int)value2);
    };
}

int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}