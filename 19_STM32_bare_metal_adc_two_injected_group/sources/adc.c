#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "adc.h"
#include "sysTick.h"
#include <stdio.h>

#define PA0_ADC_MODE (3 << 0)
#define ADC1EN (1U<<8)

//#define ADC_CH1 (1U<<0)
#define ADC_SEQ_LEN_1 0

#define CR2_ADON (1U<<0)

#define CR2_SWSTART (1U<<30)

#define SR_EOC (1U<<1)
#define CR2_CONT (1U<<1)

#define CR1_EOCIE (1U<<5)

void adc_init(){
    GPIOA->MODER |= PA0_ADC_MODE;
    RCC->APB2ENR |= ADC1EN;

    ADC1->SQR3 = 1;
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	ADC1->CR2 |= CR2_ADON;

    // ADC1->CR1 |= CR1_EOCIE;

	// NVIC_EnableIRQ(ADC_IRQn);

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

/*void ADC_IRQHandler(void){

	if((ADC1->SR & SR_EOC) != 0){
		ADC1->SR &=~ SR_EOC;

		volatile uint32_t value = ADC1->DR;
	    printf("%d\n\r", (int)value);

        // if(ADC1->SQR3  == 0) ADC1->SQR3 = 1;
        // else ADC1->SQR3 = 0;

        //adc_start_conversion();
        // delay_ms(10);
	}
} */

#define PA1_ADC_MODE (3 << 2)

#define CH0 0
#define CH1 1

//na pałe single conversion, przełączyć kanał, rozpocząć konwersję.
//spróbować użyć injected group
//spróbować użyć dma
// scan conversion mode
//enable scan
/*
void adc_init_two(){
    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;
    RCC->APB2ENR |= ADC1EN;

    //ADC->CCR 

    //ADC1->SQR3 |= CH0 | (CH1 << 5);
    ADC1->SQR3 = 0;
	ADC1->SQR1 = (1 << 20);

	ADC1->CR2 |= CR2_ADON;

        ADC1->CR1 |= CR1_EOCIE;


	NVIC_EnableIRQ(ADC_IRQn);
} */

void adc_init_two(){
    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;
    RCC->APB2ENR |= ADC1EN;
    ADC1->CR2 |= CR2_ADON;

    //ADC->CCR |= 20 << 8;
}

uint32_t adc_read_value(uint8_t channel){

    //kondensator do uziemienia? lub zwolnić tempo
    //obczaić analog watchdog

    // RCC->APB2ENR |= ADC1EN;
    // ADC1->CR2 |= CR2_ADON;

    ADC1->SQR3 = channel;
    ADC1->SQR1 = ADC_SEQ_LEN_1;
    //ADC1->CR2 &=~ CR2_CONT;
    ADC1->CR2 |= CR2_SWSTART;

    while(!(ADC1->SR & SR_EOC)){};

    volatile uint32_t value = ADC1->DR;

    // RCC->APB2ENR &=~ ADC1EN;
    // ADC1->CR2 &=~ CR2_ADON;
    

    return value;
}


//-------------------------------

void adc_init_injected_group(){
    GPIOA->MODER |= PA0_ADC_MODE;
    GPIOA->MODER |= PA1_ADC_MODE;
    RCC->APB2ENR |= ADC1EN;
     ADC1->CR2 |= CR2_ADON;
    ADC1->CR2 |= CR2_CONT;

    ADC1->CR1 |= 1<<8;  

    ADC1->CR2 |= 1 << 22; //start injected group

    ADC1->JSQR |= 1 << 20; //length of 2 channels

    ADC1->JSQR |= 0 << 10; //q3
    ADC1->JSQR |= 1 << 15; //q4

    ADC1->CR1 |= 1 << 12; 
      //ADC_JEOCIE

   
    ADC1->CR1 |= 1<<7;  
    //ADC1->CR1 |= CR1_EOCIE;
    NVIC_EnableIRQ(ADC_IRQn);
}


#define SR_JEOC (1 << 2)

void ADC_IRQHandler(void){
    if((ADC1->SR & SR_JEOC) != 0){

		ADC1->SR &=~ SR_JEOC;
        printf("Working");
        // values[0] = ADC_JDR3_JDATA;
        // values[1] = ADC_JDR4_JDATA;

        // values[0] = ADC1->JDR3;
        // values[1] = ADC1->JDR4;
        
    }
    printf("int");
}

// void adc_injected_group_read_value(){

// }