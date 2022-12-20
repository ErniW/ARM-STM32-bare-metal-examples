#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#define PA5_OUTPUT  (1 << 10)
#define LED_PIN     (1 << 5)

int main(){

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= PA5_OUTPUT;

    while(1){

        GPIOA->ODR ^= LED_PIN;

        for(long i=0; i<1500000; i++){

        };

    }

}