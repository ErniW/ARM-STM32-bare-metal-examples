#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"
#include "sysTick.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (1U<<10);  

	while(1){

        GPIOA -> ODR ^= (1U<<5);
        delay_ms(1000);

	}
}