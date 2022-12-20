#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"
#include "sysTick.h"
#include "serial.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= PA5_OUTPUT;
    
    rx_init();
     
    while(1){
		char key = rx_read();

		if(key == 'A'){
			GPIOA->ODR |= LED_PIN;
		}
		else if(key == 'B'){
            GPIOA->ODR &=~ LED_PIN;
		}

    };
}