#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "adc.h"

#define PA0_ADC_MODE (3 << 0)
#define ADC_SEQ_LEN_1 0

void adc_init(){
    GPIOA->MODER |= PA0_ADC_MODE;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->SQR1 = ADC_SEQ_LEN_1;
    ADC1->CR2 |= ADC_CR2_ADON;
}

void adc_start_conversion(void){
    ADC1->CR2 |= ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void){
    while(!(ADC1->SR & ADC_SR_EOC));
    return (ADC1->DR);
}
