#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"
#include "sysTick.h"

#define PA8_AF_MODE     (2 << 16)
#define PA9_AF_MODE     (2 << 18)
#define PA10_AF_MODE    (2 << 20)

#define PA8_AF2         (1 << 0)
#define PA9_AF2         (1 << 4)
#define PA10_AF2        (1 << 8)

#define CH1_PWM_MODE_1  (6 << 4)
#define CH2_PWM_MODE_1  (6 << 12)
#define CH3_PWM_MODE_1  (6 << 4)

int main(){

    clockSpeed_PLL();
    SysTick_Init();
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    GPIOA->MODER |= PA8_AF_MODE | PA9_AF_MODE  | PA10_AF_MODE;
    GPIOA->AFR[1] |= PA8_AF2 | PA9_AF2  | PA10_AF2;
   
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;

    TIM1->CCMR1 |= CH1_PWM_MODE_1 | CH2_PWM_MODE_1;
    TIM1->CCMR2 |= CH3_PWM_MODE_1;

    TIM1->BDTR |= TIM_BDTR_MOE;

    TIM1->ARR = 255;
    TIM1->CR1 |= TIM_CR1_CEN;


    short brightness = 0;
    short fadeAmount = 1;
    
    while(1){
        TIM1->CCR1 = brightness;
        TIM1->CCR2 = brightness;
        TIM1->CCR3 = brightness;

        brightness += fadeAmount;

        if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
        }

        delay_ms(10);
    };
}