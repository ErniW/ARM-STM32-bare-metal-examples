#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"
#include "sysTick.h"
#include "serial.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    tx_init();

    while(1){
        tx_send('k');
        tx_send('\n');
        delay_ms(1000);
    };
}