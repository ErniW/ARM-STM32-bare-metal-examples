#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

    rx_init();
    
    GPIOA->MODER |= (1U<<10);
    
    while(1){
		char key = rx_read();

		if(key == 'A'){
			GPIOA -> ODR |= (1U<<5);
		}
		else if(key == 'B'){
            GPIOA -> ODR &=~ (1U<<5);
		}

    };
}