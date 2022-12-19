#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"
#include "spi.h"

int main(){
    clockSpeed_PLL();
    SysTick_Init();

    spi_init();

    while(1){

    };
}

int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}