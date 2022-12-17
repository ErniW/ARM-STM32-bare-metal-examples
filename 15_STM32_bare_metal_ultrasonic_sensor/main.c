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

volatile int timestamp = 0;

int main(){

    clockSpeed_PLL();
    SysTick_Init();
   
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  
    // RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
     tx_init();
   // ultrasonic_timer_init();
   //button_switch_after_second_init();
//    button_measure_press_time_init();

    // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // GPIOA->MODER |= (1U<<10);
    // //GPIOA->PUPDR |= (1 << 26);
    // GPIOA->PUPDR |= (1 << 18);
    timer_init();
    button_measure_press_time_init();
    
    while(1){

        while(!(TIM1->SR & (1<<2))){};
        timestamp = TIM1->CCR2;
        timestamp /= 10;
        TIM1->CNT = 0;
        printf("%d\n", timestamp);
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
    };
}

int __io_putchar(char ch){
	tx_send(ch);
	return ch;
}