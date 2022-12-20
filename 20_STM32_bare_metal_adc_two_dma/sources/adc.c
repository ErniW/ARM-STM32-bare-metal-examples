#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "adc.h"
#include <stdio.h>

#define PA0_ADC_MODE    (3 << 0)
#define PA1_ADC_MODE    (3 << 2)

#define ADC_PRESCALER_8 (3 << 16)

#define ADC_SEQ_LEN_1   0
#define ADC_SEQ_LEN_2   (1 << 20)
#define SEQ1_CH0        (0 << 0)
#define SEQ2_CH1        (1 << 5)

#define PSIZE_16                 (1 << 11)
#define MSIZE_16                 (1 << 13)
#define DMA_CHANNEL_CLEAR        (7 << 25)
#define DMA_PERIPHERAL_TO_MEMORY (3 << 6)

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

void adc_dma_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC->CCR |= ADC_PRESCALER_8;

    ADC1->CR1 |= ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_EOCS | ADC_CR2_DMA | ADC_CR2_DDS;

    ADC1->SQR1 |= ADC_SEQ_LEN_2;
    ADC1->SQR3 |= SEQ1_CH0 | SEQ2_CH1;

    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->SR = 0;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

void adc_dma_config(uint32_t peripheral, uint32_t memory, uint16_t size){
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2_Stream0->CR &=~ DMA_PERIPHERAL_TO_MEMORY;
    DMA2_Stream0->CR |= DMA_SxCR_CIRC | DMA_SxCR_MINC | PSIZE_16 | MSIZE_16;
    DMA2_Stream0->CR &=~ DMA_CHANNEL_CLEAR;    

    DMA2_Stream0->PAR = peripheral;
    DMA2_Stream0->M0AR = memory;
    DMA2_Stream0->NDTR = size;
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}