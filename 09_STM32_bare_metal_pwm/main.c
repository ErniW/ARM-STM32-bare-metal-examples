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

    pwm_init();

    int brightness = 0;
    int fadeAmount = 2;
    
    while(1){
        TIM2->CCR1 = brightness;

        brightness = brightness + fadeAmount;

        if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
        }

        delay_ms(10);
    };
}