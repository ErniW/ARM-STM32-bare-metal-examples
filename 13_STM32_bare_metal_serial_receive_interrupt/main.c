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
    rx_interrupt_init();

    while(1){

    };
}

void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_RXNE){
        char key = USART2->DR;
        if(key == 'x'){
            GPIOA->ODR ^= LED_PIN;
        }
    }
}