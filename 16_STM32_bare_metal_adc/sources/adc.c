#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "adc.h"

#define PA0_ADC_MODE (3 << 0)
#define ADC1EN (1U<<8)

//#define ADC_CH1 (1U<<0)
#define ADC_SEQ_LEN_1 0

#define CR2_ADON (1U<<0)

#define CR2_SWSTART (1U<<30)

#define SR_EOC (1U<<1)
#define CR2_CONT (1U<<1)


void adc_init(){
    GPIOA->MODER |= PA0_ADC_MODE;
    RCC->APB2ENR |= ADC1EN;

    ADC1->SQR3 = 0;
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	ADC1->CR2 |= CR2_ADON;

   // ADC1->SMPR1 = 0;
}

void adc_start_conversion(void){
	ADC1->CR2 |= CR2_CONT;
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void){
	while(!(ADC1->SR & SR_EOC)){}

	return (ADC1->DR);
}
