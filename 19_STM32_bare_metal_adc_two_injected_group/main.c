#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

#define PA0_ADC_MODE (3 << 0)
#define PA1_ADC_MODE (3 << 2)
#define ADC1EN (1 << 8)
#define ADON (1 << 0)

#define ADC_CLOCK_PRESCALER_8 (3 << 16)

#define SWSTART (1 << 30)
#define JSWSTART (1 << 22)
#define EOCIE (1 << 5)
#define JEOCIE (1 << 7)

#define SCAN_MODE (1 << 8)
#define JAUTO (1 << 10)
#define CONTINUOUS_MODE (1 << 1)

#define INJECTED_GROUP_NUMBER_OF_CHANNELS_2 (1 << 20)
#define QUEUE3_CH0 ( 0 << 10)
#define QUEUE4_CH1 (1 << 15)

void adc_init_injected_group(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    RCC->APB2ENR |= ADC1EN;

    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;

    ADC->CCR |= ADC_CLOCK_PRESCALER_8;
    ADC1->CR2 |= ADON;

    ADC1->JSQR |= INJECTED_GROUP_NUMBER_OF_CHANNELS_2;
    ADC1->JSQR |= QUEUE3_CH0;
    ADC1->JSQR |= QUEUE4_CH1;

    ADC1->CR1 |= SCAN_MODE;  
    ADC1->CR1 |= JAUTO;
    ADC1->CR2 |= CONTINUOUS_MODE;

    ADC1->CR2 |= SWSTART;
    ADC1->CR2 |= JSWSTART;
   
    ADC1->CR1 |= EOCIE;
    ADC1->CR1 |= JEOCIE;  
    
    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void){
    if(ADC1->SR & ADC_SR_JEOC){
        
        volatile uint32_t values[2];
        values[0] = ADC1->JDR3;
        values[1] = ADC1->JDR4;
        
        printf("Values: %d, %d\n\r", (int)values[0], (int)values[1]);
        ADC1->SR &=~ ADC_SR_JEOC;
    }
}

int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}

int main(){

    clockSpeed_PLL();
    SysTick_Init();

   
    adc_init_injected_group();
    tx_init();
    

    while(1){
        printf("This should be printed\n\r");
       // printf("Values: %d, %d\n\r", (int)values[0], (int)values[1]);
    };
}





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