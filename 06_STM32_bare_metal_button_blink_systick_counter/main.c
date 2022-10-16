#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "sysTick.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;

	GPIOA->MODER |= (1U<<10);  

    volatile uint32_t prevMillis = 0;

	while(1){
        
        volatile uint32_t millis = getMillis();

        if(millis - prevMillis > 1000){
            GPIOA -> ODR ^= (1U << 5);
            prevMillis = millis;
        }

        if(!(GPIOC->IDR & (1U << 13))){
            GPIOA -> ODR |= (1U << 5);
        }
	}
}