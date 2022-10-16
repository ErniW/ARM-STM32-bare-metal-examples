#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"

int main(){

    clockSpeed_PLL();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;

	GPIOA->MODER |= (1U<<10);  

	while(1){
        
        if(GPIOC->IDR & (1U << 13)){
            GPIOA -> ODR |= (1U << 5);
        }
        else{
            GPIOA -> ODR &=~ (1U << 5);
        }
	}
}