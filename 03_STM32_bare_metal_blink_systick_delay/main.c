#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"
#include "sysTick.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= PA5_OUTPUT;

    while(1){

        GPIOA->ODR ^= LED_PIN;
        delay_ms(1000);

    }
}