#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>

#include "pll.h"
#include "timer.h"

int main(){

    clockSpeed_PLL();
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    timer_init();
    
    while(1){};
}