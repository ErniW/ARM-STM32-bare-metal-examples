#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"

char receive[20];

void send_message(char* message, int len);

int main(){
    char message[31] = "Hello from Stm32 DMA transfer\n\r";
    char message2[25] = "Second message from DMA\n\r";
   
    clockSpeed_PLL();
    SysTick_Init();
    
    tx_init();
    tx_dma_init((unsigned int)message, (unsigned int)&USART2->DR, 31);

    rx_init();
    rx_dma_init((unsigned int)receive, (unsigned int)&USART2->DR, sizeof(receive)/sizeof(char));

    bool whichMessage = false;

    while(1){
       delay_ms(500);
       whichMessage = !whichMessage;

        if(whichMessage){
            // send_message(message, 31);
            DMA1_Stream6->M0AR = (unsigned int)message;
            DMA1_Stream6->NDTR = 31;
        }
        else {
            // send_message(message2, 25);
            DMA1_Stream6->M0AR = (unsigned int)message2;
            DMA1_Stream6->NDTR = 25;
        }

        int endline = 0;
        for(int i=0; i<sizeof(receive)/sizeof(char); i++){
            if(receive[i] == '\n') {
                endline = i;
                break;
            }
        }

        DMA1_Stream5->CR &=~ 1;
        DMA1_Stream5->NDTR = sizeof(receive)/sizeof(char);
        DMA1_Stream5->CR |= 1;

        // send_message(receive, 20);

        for(int i=0; i<=endline; i++){
            tx_send(receive[i]);
        }

        DMA1_Stream6->CR |= 1;
        
    };
}

// void send_message(char* message, int len){
//     DMA1_Stream6->M0AR = (unsigned int)message;
//     DMA1_Stream6->NDTR = len;
//     DMA1_Stream6->CR |= 1;
// }

void DMA1_Stream6_IRQHandler(void){
    if(DMA1->HISR & DMA_HISR_TCIF6){
        DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
        DMA1->HIFCR |= DMA_HIFCR_CFEIF6 | (15 << 18);
    }
}

void DMA1_Stream5_IRQHandler(void){
    DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
    DMA1->HIFCR |= DMA_HIFCR_CFEIF5 | (15 << 8);
    DMA1_Stream5->CR |= 1;

    // printf("Received\n");
}


int __io_putchar(int ch){
    tx_send(ch);
    return ch;
}