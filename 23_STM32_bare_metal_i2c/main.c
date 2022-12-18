#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"
#include "i2c.h"

#define ADDRESS 0x68

int main(){
    clockSpeed_PLL();
    SysTick_Init();
    
    // uart_tx_init();
    //  uart_rx_init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    tx_init();
    i2cInit();

    i2cWrite(ADDRESS,0x6B,1,0x00);
	i2cWrite(ADDRESS,0x1B,1,0x00);
	i2cWrite(ADDRESS,0x1C,1,0x00);

    while(1){
        char accelData[6];
        char gyroData[6];

        i2cRead(ADDRESS,0x3B,6,(char*)accelData);

		int16_t ax = (accelData[0]<<8 | accelData[1]);
		int16_t ay = (accelData[2]<<8 | accelData[3]);
		int16_t az = (accelData[4]<<8 | accelData[5]);

        i2cRead(ADDRESS,0x43,6,(char*)gyroData);

		int16_t gx = (gyroData[0]<<8 | gyroData[1]);
		int16_t gy = (gyroData[2]<<8 | gyroData[3]);
		int16_t gz = (gyroData[4]<<8 | gyroData[5]);

        printf("Acc: %d, %d, %d Gyro: %d, %d, %d\n", ax,ay,az,gx,gy,gz);
        delay_ms(50);
    };
}

int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}

// void DMA1_Stream6_IRQHandler(void){
// 	if(DMA1->HISR & (1 << 21)){
// 		DMA1->HIFCR |= (1 <<21);
//         DMA1->HIFCR |= ((1 << 16) | (15 << 18));
// 	}
// }

// void DMA1_Stream5_IRQHandler(void){
//     DMA1->HIFCR |= (1U<<11);
//     DMA1->HIFCR |= ((1 << 6) | (15 << 8));
//     DMA1_Stream5->CR |= 1;

// }


// int __io_putchar(int ch){
// 	tx_send(ch);
// 	return ch;
// }

// volatile int counter = 0;

// #define TC (1 << 6)
// #define RXNE (1 << 5)

// void USART2_IRQHandler(void){
//     if(USART2->SR & TC){     
//         USART2->SR &=~ TC;
//     }
// }





    // if((USART2->SR & (1 << 4))){
      
    //     GPIOA->ODR ^= (1U<<5);
    //     //USART2->SR &=~ RXNE;
         
    //    //  USART2->SR =0;

      
       
    // }

    
      //USART2->SR &=~ TC;
//    DMA1_Stream5->CR |= 1; 
//             USART2->SR &=~ (1 << 4);
       // USART2->SR |= RXNE;
        
    
    // if(USART2->SR & RXNE){

       
        // if(receive[DMA1_Stream5->NDTR] == '\n'){
            
        // }
//    }
    
    //USART2->SR &=~ RXNE;
    // USART2->SR &=~ (1 << 6);
	// USART2->SR &=~ (1 << 5);

    // counter++;

    // if(counter == 10) {
    //     counter = 0;
    //     GPIOA->ODR ^= (1U<<5);

    //         DMA1_Stream5->CR &=~ 1;
    // DMA1_Stream5->NDTR = 5;
    // DMA1_Stream5->CR |= 1;
        
    // }





    // USART2->SR &=~ (1 << 6);
	// USART2->SR &=~ (1 << 5);

    // counter++;

    // if(counter == 10) {
    //     counter = 0;
    //     GPIOA->ODR ^= (1U<<5);

    //         DMA1_Stream5->CR &=~ 1;
    // DMA1_Stream5->NDTR = 5;
    // DMA1_Stream5->CR |= 1;
        
    // }


//tx_send(receive);
//DMA1_Stream5->CR |= 1;

//  DMA1_Stream6->M0AR = receive;
//         DMA1_Stream6->NDTR = 1;
//         DMA1_Stream6->CR |= 1;

        // tx_send(testing+'0');
        // tx_send('\n');

    //    USART2->SR &=~ (1 << 6);
	// USART2->SR &=~ (1 << 5);