#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdio.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "ultrasonic.h"

int main(){

    clockSpeed_PLL();
    SysTick_Init();
    tx_init();

    unsigned long prevTime = 0;
    ultrasonic_int_init();

    while(1){
        unsigned long time = getMillis();

        if(time - prevTime > 100){
            ultrasonic_start_measure();
            prevTime = time;
        }

    };

/*
    //blocking version
    ultrasonic_init();

    while(1){
        int distance = ultrasonic_measure();
        printf("%d\n", distance);
        delay_ms(80);
    }
*/

}

int __io_putchar(char ch){
    tx_send(ch);
    return ch;
}