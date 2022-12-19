#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)

int main(){

    clockSpeed_PLL();
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= PA5_OUTPUT;  


    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    //__disable_irq();

    TIM2->CR1 &=~ TIM_CR1_CEN;

    TIM2->PSC = ((APB1_FREQ) * 2 / 10000) - 1; //9000 - 1
    TIM2->ARR = 10000 - 1;
    TIM2->CNT = 0;

    //TIM2->EGR  |= TIM_EGR_UG;
    TIM2->DIER |= TIM_DIER_UIE;

    TIM2->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM2_IRQn);

    //__enable_irq();
    
    while(1){

    };
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &=~ TIM_SR_UIF;
        GPIOA->ODR ^= LED_PIN;
    }
}