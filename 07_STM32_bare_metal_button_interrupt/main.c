#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "sysTick.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)
#define BUTTON_PIN  (1 << 13)
#define EXTI_C13    (2 << 4)

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    
	GPIOA->MODER |= PA5_OUTPUT;  

    __disable_irq();

    SYSCFG->EXTICR[3] |= EXTI_C13;
    EXTI->IMR |= BUTTON_PIN;
	EXTI->FTSR |= BUTTON_PIN;

    NVIC_EnableIRQ(EXTI15_10_IRQn);

    __enable_irq();

	while(1){

	}
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & BUTTON_PIN){
	    EXTI->PR |= BUTTON_PIN;
		GPIOA->ODR ^= LED_PIN;
	}
}
