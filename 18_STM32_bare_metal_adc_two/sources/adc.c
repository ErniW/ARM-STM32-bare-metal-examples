#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "adc.h"
#include <stdio.h>

#define PA0_ADC_MODE    (3 << 0)
#define PA1_ADC_MODE    (3 << 2)

#define ADC_PRESCALER_8 (3 << 16)

#define ADC_SEQ_LEN_1   0

void adc_init(){
    GPIOA->MODER |= PA0_ADC_MODE;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->SQR1 = ADC_SEQ_LEN_1;
    ADC1->CR2 |= ADC_CR2_ADON;
}

void adc_int_init(){
    ADC1->CR1 |= ADC_CR1_EOCIE;
    NVIC_EnableIRQ(ADC_IRQn);
}

void adc_start_conversion(void){
    ADC1->CR2 |= ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void){
    while(!(ADC1->SR & ADC_SR_EOC));
    return (ADC1->DR);
}

void ADC_IRQHandler(void){

    if((ADC1->SR & ADC_SR_EOC) != 0){
        ADC1->SR &=~ ADC_SR_EOC;

        volatile uint32_t value = ADC1->DR;
        printf("%d\n\r", (int)value);
    }
}

void adc_init_two(){
    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->CR2 |= ADC_CR2_ADON;
    ADC->CCR |= ADC_PRESCALER_8;
}

uint32_t adc_read_channel(uint8_t channel){
    ADC1->SQR3 = channel;
    ADC1->SQR1 = ADC_SEQ_LEN_1;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    while(!(ADC1->SR & ADC_SR_EOC)){};

    return ADC1->DR;
}