#include "pwm.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

void pwm_init(){
    GPIOA->AFR[0] |= (1 << 20);
    GPIOA->MODER |= (1 << 11);

    TIM2->PSC = 0;
    TIM2->ARR = 255;
    TIM2->CNT = 0;
    TIM2->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM2->CCER |= 1;
    TIM2->CR1 |= 1;
}

void pwm_rgb_init(){
    GPIOA->AFR[1] |= (1 << 0) | (1 << 4) | (1 << 8);
    GPIOA->MODER |= (2 << 16) | (2 << 18) | (2 << 20);

    TIM1->CCER |= (1 << 0) | (1 << 4) | (1 << 8);

    TIM1->CCMR1 |= (6 << 4);
    TIM1->CCMR1 |= (6 << 12);
    TIM1->CCMR2 |= (6 << 4);
    TIM1->BDTR |= TIM_BDTR_MOE;
    
    TIM1->PSC = 0;
    TIM1->ARR = 255;
    TIM1->CNT = 0;
    TIM1->CR1 |= 1;
}

void pwm_servo_init(){
    GPIOA->AFR[0] |= (1 << 20);
    GPIOA->MODER |= (1 << 11);

    TIM2->PSC = 90-1;
    TIM2->ARR = 20000;
    TIM2->CNT = 0;
    TIM2->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM2->CCER |= 1; 
    TIM2->CR1 |= 1;
}