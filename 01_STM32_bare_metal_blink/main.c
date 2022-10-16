#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

int main(){

    RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (1U<<10);

	while(1){

        GPIOA -> ODR ^= (1U<<5);

        for(int i=0; i<1500000; i++){
            __asm("nop");
        };

	}

}