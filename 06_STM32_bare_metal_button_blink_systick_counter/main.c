#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "sysTick.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)
#define BUTTON_PIN  (1 << 13)

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	GPIOA->MODER |= PA5_OUTPUT;  

    volatile uint32_t prevMillis = 0;

	while(1){
        
        volatile uint32_t millis = getMillis();

        if(millis - prevMillis > 1000){
            GPIOA->ODR ^= LED_PIN;
            prevMillis = millis;
        }

        if(!(GPIOC->IDR & BUTTON_PIN)){
            GPIOA->ODR |= LED_PIN;
        }
	}
}