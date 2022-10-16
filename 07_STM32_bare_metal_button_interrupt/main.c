#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "sysTick.h"
#include "interrupt.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();
    pc13_interrupt_init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;

	GPIOA->MODER |= (1U<<10);  

	while(1){

	}
}