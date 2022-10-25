#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "timer.h"
#include "pll.h"

void timer_init(){
    __disable_irq();

    GPIOA -> MODER |= (1U<<10);

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    GPIOA->AFR[0] |= (1U << 20);

    TIM2->CR1 &=~ TIM_CR1_CEN;

    TIM2->PSC = ((APB1_FREQ) * 2 / 10000) - 1;
    TIM2->ARR = 10000 - 1;
    TIM2->CNT = 0;

    TIM2->EGR  |= TIM_EGR_UG;
    TIM2->DIER |= TIM_DIER_UIE;

    TIM2->CR1 |= 1;

    NVIC_EnableIRQ(TIM2_IRQn);

    __enable_irq();
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &=~ TIM_SR_UIF;
        GPIOA->ODR ^= (1U << 5);
    }
}