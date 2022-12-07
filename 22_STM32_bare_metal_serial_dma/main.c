#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

 char receiveBuffer[12];
char receive[20];

int main(){
    char message[31] = "Hello from Stm32 DMA transfer\n\r";
    char message2[25] = "Second message from DMA\n\r";
   

    clockSpeed_PLL();
    SysTick_Init();
    
    uart_tx_init();
    uart_tx_dma_init((unsigned int)message, (unsigned int)&USART2->DR, 31);

    uart_rx_init();
    uart_rx_dma_init((unsigned int)receive, (unsigned int)&USART2->DR, sizeof(receive)/sizeof(char));

    bool whichMessage = false;

    RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (1U<<10);

    while(1){
       delay_ms(500);
       whichMessage = !whichMessage;

        if(whichMessage){
            DMA1_Stream6->M0AR = (unsigned int)message;
            DMA1_Stream6->NDTR = 31;
        }
        else {
            DMA1_Stream6->M0AR = (unsigned int)message2;
            DMA1_Stream6->NDTR = 25;
        }

        char test[] = "abcd";
       // if(strcmp(receive, test) == 0) GPIOA->ODR ^= (1U<<5);

        

        int endline = 0;
        for(int i=0; i<sizeof(receive)/sizeof(char); i++){
            if(receive[i] == '\n') {
                endline = i;
                DMA1_Stream5->CR &=~ 1;
                DMA1_Stream5->NDTR = sizeof(receive)/sizeof(char);
                DMA1_Stream5->CR |= 1;
                break;
            }
        }

       // if(endline != 0) tx_send('\n');
       //if(endline != 0) tx_send(' ');
         for(int i=0; i<=endline; i++){
            tx_send(receive[i]);
        }
        
        

        DMA1_Stream6->CR |= 1;
    };
}

void DMA1_Stream6_IRQHandler(void){
	if(DMA1->HISR & (1 << 21)){
		DMA1->HIFCR |= (1 <<21);
        DMA1->HIFCR |= ((1 << 16) | (15 << 18));
	}
}

void DMA1_Stream5_IRQHandler(void){
    DMA1->HIFCR |= (1U<<11);
    DMA1->HIFCR |= ((1 << 6) | (15 << 8));
    DMA1_Stream5->CR |= 1;

}


int __io_putchar(int ch){
	tx_send(ch);
	return ch;
}

volatile int counter = 0;

#define TC (1 << 6)
#define RXNE (1 << 5)

void USART2_IRQHandler(void){
    if(USART2->SR & TC){     
        USART2->SR &=~ TC;
    }
}





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