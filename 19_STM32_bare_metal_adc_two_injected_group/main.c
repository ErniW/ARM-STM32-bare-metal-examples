#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

volatile uint32_t values[2];

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

    tx_init();
    adc_init();
    adc_init_injected_group();

    while(1){
        
    };
}

int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}

#define SR_JEOC (1 << 2)

// void ADC_IRQHandler(void){
//     if((ADC1->SR & SR_JEOC) != 0){

// 		ADC1->SR &=~ SR_JEOC;

//         // values[0] = ADC_JDR3_JDATA;
//         // values[1] = ADC_JDR4_JDATA;

//         values[0] = ADC1->JDR3;
//         values[1] = ADC1->JDR4;
//         printf("%d, %d\n\r", (int)values[0], (int)values[1]);
//     }
// }