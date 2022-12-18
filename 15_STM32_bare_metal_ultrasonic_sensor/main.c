#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>

#include "pll.h"
#include "pwm.h"
#include "sysTick.h"
#include "serial.h"
#include "timer.h"


#define CC1F_INT (1 << 1)

// volatile int timestamp = 0;

int main(){

    clockSpeed_PLL();
    SysTick_Init();
   
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  
     tx_init();

    ultrasonic_timer_init();

    ultrasonic_init_interrupt();

    unsigned long prevTime = 0;

    while(1){
        unsigned long time = getMillis();

        if(time - prevTime > 100){

            ultrasonic_start_measure();

            prevTime = time;
        }

        // ultrasonic_measure();
        // delay_ms(80);
    };
}

int __io_putchar(char ch){
	tx_send(ch);
	return ch;
}


        // while(!(TIM1->SR & (1<<2))){};
        // timestamp = TIM1->CCR2;
        // timestamp /= 10;
        // TIM1->CNT = 0;
        // printf("%d\n", timestamp);


        //TIM1->CR1 |= 1;
       

        //  if(GPIOA->IDR & (1U << 9)){
        //     GPIOA -> ODR |= (1U << 5);
        // }
        // else{
        //     GPIOA -> ODR &=~ (1U << 5);
        // }

        //  if(GPIOC->IDR & (1U << 13)){
        //     GPIOA -> ODR |= (1U << 5);
        // }
        // else{
        //     GPIOA -> ODR &=~ (1U << 5);
        // }

        //  if(GPIOA->IDR & (1U << 9)){
        //     GPIOA -> ODR |= (1U << 5);
        // }
        // else{
        //     GPIOA -> ODR &=~ (1U << 5);
        // }

        // volatile int value = ultrasonic_measure_distance();
        // while(!(TIM1->SR &  CC1F_INT)){}
        // printf("test");