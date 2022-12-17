#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "timer.h"
#include "pll.h"
#include "systick.h"
#include "stdio.h"

void timer_init(){
    __disable_irq();

    GPIOA -> MODER |= (1U<<10);

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    GPIOA->AFR[0] |= (1U << 20);

    TIM2->CR1 &=~ TIM_CR1_CEN;

    TIM2->PSC = ((APB1_FREQ) * 2 / 10000) - 1;
    TIM2->ARR = 10000 - 1;
    TIM2->CNT = 0;

    TIM2->EGR  |= TIM_EGR_UG;
    TIM2->DIER |= TIM_DIER_UIE;

    TIM2->CR1 |= 1;

    NVIC_EnableIRQ(TIM2_IRQn);

    __enable_irq();
}

volatile int timestamp = 0;

#define CC2IF (1 << 2)

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &=~ TIM_SR_UIF;
        GPIOA->ODR ^= (1U << 5);
    }
}

#define BUTTON_PIN (1U<<13)

void button_switch_after_second_init(){

	__disable_irq();

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;
    GPIOA -> MODER |= (1U<<10);
    

    SYSCFG->EXTICR[3] |= (2 << 4);

	EXTI->IMR |= BUTTON_PIN;
	EXTI->FTSR |= BUTTON_PIN;

	NVIC_EnableIRQ(EXTI15_10_IRQn);

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = ((APB1_FREQ) * 2 / 10000) - 1;
    TIM2->ARR = 10000 - 1;
    TIM2->CNT = 0;
    
    TIM2->EGR  |= TIM_EGR_UG;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |=  TIM_CR1_OPM;
    //TIM2->CR1 &=~ 1;

    TIM2->SR &=~ TIM_SR_UIF;
    NVIC_EnableIRQ(TIM2_IRQn);
	__enable_irq();

}

// void EXTI15_10_IRQHandler(void){
// 	if(EXTI->PR & BUTTON_PIN){
// 	    EXTI->PR |= BUTTON_PIN;
//         TIM2->CR1 |= 1;
//         //printf("test");
//         //TIM2->DIER |= TIM_DIER_UIE;
// 		//GPIOA->ODR ^= (1U<<5);
// 	}
// }

// void TIM2_IRQHandler(void) {
//     if (TIM2->SR & TIM_SR_UIF) {
//         TIM2->SR &=~ TIM_SR_UIF;
//         GPIOA->ODR ^= (1U << 5);
//     }
// }


void button_measure_press_time_init(){
   __disable_irq();

//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;
   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
   GPIOA->MODER |= (1 << 19);
   GPIOA->AFR[1] |= (1 << 4);

   RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

   TIM1->PSC = ((APB2_FREQ * 2) / 10000) - 1;

   TIM1->CCMR1 |= (1<<8);
   TIM1->CCER |= (5<<5);
   TIM1->CCER |= (1<<4);
   //TIM1->CR1 |=  TIM_CR1_OPM;

    TIM1->DIER |= (1 << 2);

    NVIC_EnableIRQ(TIM1_CC_IRQn);

   TIM1->CR1 |= TIM_CR1_CEN;
   __enable_irq();
}


void TIM1_CC_IRQHandler(void){
    if(TIM1->SR & CC2IF){
        timestamp = TIM1->CCR2;
        timestamp /= 10;
        TIM1->CNT = 0;
        printf("%d\n", timestamp);
    }
}

//#define CC1F_INT (1 << 1)

// void TIM1_CC_IRQHandler(void) {
//     printf("test");
//     if (TIM1->SR & CC1F_INT) {
//         TIM1->SR &=~ CC1F_INT;
//         GPIOA->ODR ^= (1U << 5);
//     }
// }



void ultrasonic_timer_init(){

}

void ultrasonic_measure(){

}

//D5 /D4 to PB4/ PB5 to TIM3CH1 / -

//PB4 AF2

// 1mhz to jest okres 1 us

/*

    How to make it work:
    1. Send 10 us pulse (set systick delay to 10 us)
    2. Set timer to receive value

    Jak mierzyć rising edge and falling edge (zmiana polaryzacji)
*/


// void ultrasonic_timer_init(){

//     GPIOB->MODER |= (1 << 10);

//     // GPIOB->MODER |= (1 << 9);
//     // GPIOB->AFR[0] |= (2 << 20);

//     RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

//     TIM3->CR1 &=~ TIM_CR1_CEN;
//     TIM3->CR1 |=  TIM_CR1_OPM;

//     TIM3->PSC = ((APB1_FREQ) * 2 / 10000) - 1;
//     TIM3->ARR = 0xFFFF;
//     TIM3->CNT = 0;

//     TIM3->EGR  |= TIM_EGR_UG;
//     //TIM3->DIER |= TIM_DIER_UIE;

//     TIM3->CR1 |= TIM_CR1_CEN;

//     //NVIC_EnableIRQ(TIM3_IRQn);
//     SYSCFG->EXTICR[1] |= (1<< 1);
// }

// volatile uint16_t time = 0;



// int ultrasonic_measure_distance(){
//     GPIOB->ODR |= (1 << 5);
//     delay_ms(20);
//     GPIOB->ODR &=~ (1 << 5);
//     TIM3->CNT = 0;
//     TIM3->CR1 |= TIM_CR1_CEN;

// };

// void TIM3_IRQHandler(void) {
//     if (TIM3->SR & TIM_SR_UIF) {
//         TIM3->SR &=~ TIM_SR_UIF;
//         time = TIM3->CNT;
//     }
// }