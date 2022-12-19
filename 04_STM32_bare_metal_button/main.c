#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)
#define BUTTON_PIN  (1 << 13)

int main(){

    clockSpeed_PLL();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	GPIOA->MODER |= PA5_OUTPUT;  

	while(1){
        
        if(GPIOC->IDR & BUTTON_PIN){
            GPIOA->ODR &=~ LED_PIN;
        }
        else{
            GPIOA->ODR |= LED_PIN;
        }
        
	}
}