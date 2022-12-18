#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "timer.h"
#include "pll.h"
#include "systick.h"
#include "stdio.h"
#include<stdbool.h>

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

int timestamp = 0;

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

#define CC1IF (1 << 1)

void pre_count_timer(){
//    // TIM1->CCMR1 |= (1<<8);
//     RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
//     TIM1->PSC = ((APB2_FREQ * 2) / 10000) - 1;
//    TIM1->CCR1 = 5000;
//    //TIM1->ARR = 40000;
//    TIM1->CCMR1 |= (1 << 4) | (1 << 7);
//      TIM1->BDTR |= TIM_BDTR_MOE;
// TIM1->CCER |= (1<<0);
   
//    TIM1->EGR  |= (1<<1);
//     TIM1->DIER |= (1 << 1) ;

//    TIM1->CR1 |= TIM_CR1_CEN;
//     NVIC_EnableIRQ(TIM1_CC_IRQn);
//     TIM1->CNT = 0;

/*

Procedure:
1. Select the counter clock (internal, external, prescaler).
2. Write the desired data in the TIMx_ARR and TIMx_CCRx registers.
3. Set the CCxIE bit if an interrupt request is to be generated.
4. Select the output mode. For example:
– Write OCxM = 011 to toggle OCx output pin when CNT matches CCRx
– Write OCxPE = 0 to disable preload register
– Write CCxP = 0 to select active high polarity
– Write CCxE = 1 to enable the output
5. Enable the counter by setting the CEN bit in the TIMx_CR1 register
*/

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC = ((APB2_FREQ * 2) / 10000) - 1;
    //TIM1->ARR = 10000;
    
    TIM1->DIER |= (1 << 1) | (1<<0);
    TIM1->CCMR1 |= (3 << 4);
    TIM1->CCMR1 &=~ (1 << 3);
    TIM1->CCER |= (1<<1);
    TIM1->CCER &=~ (1<<0);

    TIM1->CCR1 = 30000;
    TIM1->CR1 |= 1;
    TIM1->CNT = 0;
    NVIC_EnableIRQ(TIM1_CC_IRQn);

}
/*
void TIM1_CC_IRQHandler(void){
    if(TIM1->SR & CC2IF){
        TIM1->SR  &=~ CC2IF;
        timestamp = TIM1->CCR2;
        timestamp /= 10;
        //TIM1->CNT = 0;
        printf("%d\n", timestamp);
        // if (timestamp > 6000) {
        //     //TIM1->DIER &=~ (1 << 2);
        //     TIM1->CCR2 = 0;
        //     TIM1->SR  &=~ CC2IF;
        //     timestamp = 0;
        // }
    }
        // uint32_t a = TIM1->CNT;
      
        //  printf("%d, %ld\n", TIM1->CCR1, a);

    if(TIM1->SR & CC1IF){
        TIM1->SR  &=~ CC1IF;
         //uint32_t a = TIM1->CNT;
        
         printf("DONE\n");
        
        //  TIM1->DIER &=~ (1 << 2);
        //  TIM1->CCER &=~ (1 << 0);
        // TIM1->SR  &=~ CC2IF;
         //TIM1->CCR2 = 0;
       // TIM1->CNT = 0;
    }
} 
*/

//#define CC1F_INT (1 << 1)

// void TIM1_CC_IRQHandler(void) {
//     printf("test");
//     if (TIM1->SR & CC1F_INT) {
//         TIM1->SR &=~ CC1F_INT;
//         GPIOA->ODR ^= (1U << 5);
//     }
// }


/*
    1. ustawienie timera na 1 mhz
    2. Wyślij sygnał przez 10us
    3. ustaw counter na 0.
    4. Mierz czas.

*/


void ultrasonic_timer_init(){
   __disable_irq();

//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;
   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
   GPIOA->MODER |= (1 << 19);
   GPIOA->AFR[1] |= (1 << 4);

   GPIOA->MODER |= (1 << 16);

   RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

   //TIM1->PSC = ((APB2_FREQ * 2) / 10000) - 1;
    //TIM1->PSC = ((APB2_FREQ * 2) / 180) - 1;

    TIM1->PSC = 180 - 1;

   TIM1->CCMR1 |= (1<<8);
   TIM1->CCER |= (5<<5);
   TIM1->CCER |= (1<<4);
   //TIM1->CR1 |=  TIM_CR1_OPM;

    //  TIM1->DIER |= (1 << 2);

    // NVIC_EnableIRQ(TIM1_CC_IRQn);

   TIM1->CR1 |= TIM_CR1_CEN;
   __enable_irq();
}

// void TIM1_CC_IRQHandler(void) {
//     if (TIM1->SR & CC2IF) {
//         TIM1->SR &=~ CC2IF;
        
//     }
// }

volatile int distance = 0;

volatile int timestamp2 = 0;

void ultrasonic_measure(){
    // printf("Start\n");
    TIM1->SR &=~ CC2IF;
    GPIOA->ODR |= (1 << 8);
    TIM1->CNT = 0;
    while(TIM1->CNT != 10){};
    GPIOA->ODR &=~ (1 << 8);
    // printf("Sent\n");
    while(!(TIM1->SR & CC2IF));
    timestamp = TIM1->CCR2;
    // printf("A %d\n", timestamp);
    while(!(TIM1->SR & CC2IF));
    timestamp2 = TIM1->CCR2;
    //  printf("B %d\n", timestamp2);
    
     distance =  timestamp2 - timestamp;
     distance = distance * 0.034 / 2;
     printf("%d\n", distance);
}

int getDist(){
    return distance;
}

void ultrasonic_init_interrupt(){
    __disable_irq();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (1 << 19);
    GPIOA->AFR[1] |= (1 << 4);

    GPIOA->MODER |= (1 << 16);

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC = 180 - 1;

    TIM1->CCMR1 |= (1<<8);
    TIM1->CCER |= (5<<5);
    TIM1->CCER |= (1<<4);
    TIM1->DIER |= (1 << 2);

    TIM1->DIER |= (1 << 1) | (1<<0);
    TIM1->CCMR1 |= (3 << 4);
    TIM1->CCMR1 &=~ (1 << 3);
    TIM1->CCER |= (1<<1);
    TIM1->CCER &=~ (1<<0);
     TIM1->CCR1 = 10;

    TIM1->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM1_CC_IRQn);
    __enable_irq();
}

bool measureEdge = false;
volatile bool trig = false;

void TIM1_CC_IRQHandler(void) {
    if (TIM1->SR & CC2IF) {
        TIM1->SR &=~ CC2IF;
        if(!measureEdge){
            //  TIM1->CNT = 0;
            timestamp = TIM1->CCR2;
            measureEdge = true;
            //TIM1->CNT = 0;
            //  printf("Rising\n");
        }
        else{
            timestamp2 = TIM1->CCR2;
            distance = timestamp2 - timestamp;
            distance = distance * 0.034 / 2;

            if(distance < 0) distance = 0;
            measureEdge = false;
            //  printf("Falling\n");
            printf("%d\n",distance);
            // TIM1->CNT = 0;
            TIM1->CR1 &=~ TIM_CR1_CEN;
            //trig = true;
            TIM1->SR &=~ CC1IF;
        }   
    }

    else if((TIM1->SR & CC1IF) ){
        //TIM1->SR &=~ CC1IF;
        GPIOA->ODR &=~ (1 << 8);
       // TIM1->DIER &=~ (1 << 1);
       //TIM1->CCER &=~ 1;
        //  printf("send stop\n");
        
    }

    if(TIM1->SR & TIM_SR_UIF){
        TIM1->SR &=~ TIM_SR_UIF;
        // TIM1->SR &=~ CC2IF;
        // TIM1->SR &=~ CC1IF;
        // printf("%d %d overflow\n", timestamp, timestamp2);
        //TIM1->CCR2 = 0;
        // distance = 0;
        //measureEdge = false;
        TIM1->CR1 &=~ TIM_CR1_CEN;
    }
}

void ultrasonic_start_measure(){
    //  printf("send----------\n");
    //  TIM1->DIER |= (1 << 1);

    TIM1->CR1 |= TIM_CR1_CEN;
    measureEdge = false;
    
    TIM1->CNT = 0;
    GPIOA->ODR |= (1 << 8);

    
    

    // TIM1->CR1 |= TIM_CR1_CEN;
    // TIM1->CNT = 0;

    // GPIOA->ODR |= (1 << 8);
    // while(TIM1->CNT != 10);
    // GPIOA->ODR &=~ (1 << 8);
    
}