#include "interrupt.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#define BUTTON_PIN (1U<<13)

void pc13_interrupt_init(void){
	__disable_irq();

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;

    SYSCFG->EXTICR[3] |= (2 << 4);

	EXTI->IMR |= BUTTON_PIN;
	EXTI->FTSR |= BUTTON_PIN;

	NVIC_EnableIRQ(EXTI15_10_IRQn);

	__enable_irq();
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & BUTTON_PIN){
	    EXTI->PR |= BUTTON_PIN;
		GPIOA->ODR ^= (1U<<5);
	}
}
