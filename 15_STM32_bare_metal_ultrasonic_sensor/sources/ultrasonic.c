#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "ultrasonic.h"
#include "serial.h"
#include "pll.h"

#include<stdbool.h>
#include<stdio.h>

#define PA8_OUTPUT  (1 << 16)
#define PA9_AF_MODE (1 << 19)
#define PA9_AF1     (1 << 4)

#define TRIG_PIN    (1 << 8)

#define TIM1_CH2_INPUT_TI2          (1 << 8)
#define TIM1_CH2_INPUT_BOTH_EDGES   (5 << 5)
#define TIM1_CH1_OUTPUT_MODE_TOGGLE (3 << 4)

void ultrasonic_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    GPIOA->MODER |= PA8_OUTPUT;
    GPIOA->MODER |= PA9_AF_MODE;
    GPIOA->AFR[1] |= PA9_AF1;

    TIM1->PSC = 180 - 1;
    TIM1->CCMR1 |= TIM1_CH2_INPUT_TI2;
    TIM1->CCER |= TIM1_CH2_INPUT_BOTH_EDGES;
    TIM1->CCER |= TIM_CCER_CC2E;

    TIM1->CR1 |= TIM_CR1_CEN;
};

int ultrasonic_measure(){
    int timestamp = 0;
    int timestamp2 = 0;

    TIM1->SR &=~ TIM_SR_CC2IF;
    GPIOA->ODR |= TRIG_PIN;
    TIM1->CNT = 0;

    while(TIM1->CNT != 10){};
    GPIOA->ODR &=~ TRIG_PIN;

    while(!(TIM1->SR & TIM_SR_CC2IF));
    timestamp = TIM1->CCR2;
    while(!(TIM1->SR & TIM_SR_CC2IF));
    timestamp2 = TIM1->CCR2;
    
    int distance =  timestamp2 - timestamp;
    distance = distance * 0.034 / 2;
    return distance;
};

void ultrasonic_int_init(){
    __disable_irq();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    GPIOA->MODER |= PA8_OUTPUT;
    GPIOA->MODER |= PA9_AF_MODE;
    GPIOA->AFR[1] |= PA9_AF1;

    TIM1->PSC = 180 - 1;
    TIM1->CCMR1 |= TIM1_CH2_INPUT_TI2;
    TIM1->CCER |= TIM1_CH2_INPUT_BOTH_EDGES;
    TIM1->CCER |= TIM_CCER_CC2E;
    TIM1->DIER |= TIM_DIER_CC2IE | TIM_DIER_CC1IE | TIM_DIER_UIE;

    TIM1->CCMR1 |= TIM1_CH1_OUTPUT_MODE_TOGGLE;
    TIM1->CCMR1 &=~ (1 << 3);
    TIM1->CCER |= TIM_CCER_CC1P;
    TIM1->CCER &=~ TIM_CCER_CC1E;
    TIM1->CCR1 = 10;
    TIM1->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM1_CC_IRQn);
    __enable_irq();
};

volatile bool pulseBeginEdge = true;
volatile int timestamp = 0;
volatile int timestamp2 = 0;
volatile int distance = 0;

void ultrasonic_start_measure(){
    TIM1->CR1 |= TIM_CR1_CEN;
    pulseBeginEdge = true;
    
    TIM1->CNT = 0;
    GPIOA->ODR |= TRIG_PIN;
};

void TIM1_CC_IRQHandler(void) {
    if(TIM1->SR & TIM_SR_CC2IF){
        TIM1->SR &=~ TIM_SR_CC2IF;

        if(pulseBeginEdge){
            timestamp = TIM1->CCR2;
            pulseBeginEdge = false;
        }
        else{
            timestamp2 = TIM1->CCR2;
            distance = timestamp2 - timestamp;
            distance = distance * 0.034 / 2;

            if(distance < 0) distance = 0;

            pulseBeginEdge = true;

            printf("%d\n", distance);

            TIM1->CR1 &=~ TIM_CR1_CEN;
            TIM1->SR &=~ TIM_SR_CC1IF;
        }

    }
    else if(TIM1->SR & TIM_SR_CC1IF){
        GPIOA->ODR &=~ TRIG_PIN;
    }

    if(TIM1->SR & TIM_SR_UIF){
        TIM1->SR &=~ TIM_SR_UIF;
        TIM1->CR1 &=~ TIM_CR1_CEN;
    }
};