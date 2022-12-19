#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "adc.h"
#include "sysTick.h"
#include <stdio.h>

//#define ADC_CH1 (1U<<0)
// #define ADC_SEQ_LEN_1 0
// #define CR2_SWSTART (1U<<30)

// #define SR_EOC (1U<<1)
// #define CR2_CONT (1U<<1)

// #define CR1_EOCIE (1U<<5)
// #define CH0 0
// #define CH1 1

// void adc_init_two(){
//     GPIOA->MODER |= PA0_ADC_MODE;
//     GPIOA->MODER |= PA1_ADC_MODE;
//     RCC->APB2ENR |= ADC1EN;
//     ADC1->CR2 |= CR2_ADON;
    
//     ADC->CCR |= 3 << 16;
// }

//----------------------

#define ADC1EN (1 << 8)
#define ADON (1 << 0)
#define SWSTART (1 << 30)
#define ADC_CLOCK_PRESCALER_8 (3 << 16)

#define PA0_ADC_MODE (3 << 0)
#define PA1_ADC_MODE (3 << 2)

#define SCAN_MODE (1 << 8)
#define CONTINUOUS_MODE (1 << 1)
#define EOCS (1 << 10)
#define DMA_ENABLE (1 << 8)
#define DMA_CONTINUOUS (1 << 9)

#define ADC_SEQUENCE_LENGTH_2 (1 << 20)
#define SEQ1_CH0 (0 << 0)
#define SEQ2_CH1 (1 << 5)

#define ENABLE_DMA2 (1 << 22)
#define ENABLE_DMA_STREAM (1 << 0)
#define PERIPHERAL_TO_MEMORY (3 << 6)
#define CIRCULAR_MODE (1 << 8)
#define MINC (1 << 10)
#define PSIZE_16 (1 << 11)
#define MSIZE_16 (1 << 13)
#define DMA_CHANNEL (7 << 25)


void adc_dma_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;
    RCC->APB2ENR |= ADC1EN;
    ADC->CCR |= ADC_CLOCK_PRESCALER_8;

    ADC1->CR1 |= SCAN_MODE;
    ADC1->CR2 |= CONTINUOUS_MODE | EOCS | DMA_ENABLE | DMA_CONTINUOUS;

    ADC1->SQR1 |= ADC_SEQUENCE_LENGTH_2;
    ADC1->SQR3 |= SEQ1_CH0 | SEQ2_CH1;

    ADC1->CR2 |= ADON;
    ADC1->SR = 0;
    ADC1->CR2 |= SWSTART;

    RCC->AHB1ENR |= ENABLE_DMA2;

    DMA2_Stream0->CR &=~ PERIPHERAL_TO_MEMORY;
    DMA2_Stream0->CR |= CIRCULAR_MODE;
    DMA2_Stream0->CR |= MINC;
    DMA2_Stream0->CR |= PSIZE_16 | MSIZE_16;
    DMA2_Stream0->CR &=~ DMA_CHANNEL;
}

void dma_config(uint32_t srcAdd, uint32_t destAdd, uint16_t size){
    DMA2_Stream0->NDTR = size;
    DMA2_Stream0->PAR = srcAdd;
    DMA2_Stream0->M0AR = destAdd;
    DMA2_Stream0->CR |= ENABLE_DMA_STREAM;
}

void adc_start(){
    ADC1->SR = 0;              
	ADC1->CR2 |= (1<<20);
	ADC1->CR2 |= 1<<22;   
}

#define ADC_WATCHDOG_CHANNEL_1 (1 << 0)
#define AWDEN ( 1 << 23)
#define AWDSGL (1 << 9)
#define AWDIE ( 1<<6 )
#define SR_AWD (1 <<0)

void adc_watchdog(){
    ADC1->CR1 |= ADC_WATCHDOG_CHANNEL_1;
    ADC1->CR1 |= AWDEN | AWDSGL | AWDIE;

    ADC1->HTR = 3000;
    ADC1->LTR = 1000;

    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void){
    if((ADC1->SR & SR_AWD) != 0){
		ADC1->SR &=~ SR_AWD;
        printf("value exceeded\n\r");
    }
}