#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "pwm.h"
#include "sysTick.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    pwm_servo_init();
    
    while(1){
        TIM2->CCR1 = 500;
        delay_ms(1000);

        TIM2->CCR1 = 1500;
        delay_ms(1000);

        TIM2->CCR1 = 2500;
        delay_ms(1000);
    };
}