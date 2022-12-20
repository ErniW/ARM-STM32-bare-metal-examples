#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"
#include "sysTick.h"

#define PA5_AF_MODE (1 << 11)
#define PA5_AF1     (1 << 20)

int main(){

    clockSpeed_PLL();
    SysTick_Init();
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    GPIOA->MODER |= PA5_AF_MODE;
    GPIOA->AFR[0] |= PA5_AF1;

    TIM2->PSC = 90-1;
    TIM2->ARR = 20000;

    TIM2->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM2->CCER |= TIM_CCER_CC1E; 
    TIM2->CR1 |= TIM_CR1_CEN;
    
    while(1){
        TIM2->CCR1 = 500;
        delay_ms(1000);

        TIM2->CCR1 = 1500;
        delay_ms(1000);

        TIM2->CCR1 = 2500;
        delay_ms(1000);
    };
}