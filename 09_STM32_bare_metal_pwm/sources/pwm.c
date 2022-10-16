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