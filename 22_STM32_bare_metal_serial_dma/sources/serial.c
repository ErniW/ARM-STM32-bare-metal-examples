#include "serial.h"
#include "pll.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"
/*
#define BAUDRATE 115200
#define UART2EN (1U<<17)

#define CR1_RE (1U<<2)
#define CR1_TE (1U<<3)
#define CR1_UE (1U<<13)

#define SR_RXNE (1U<<5)
#define SR_TXE (1U<<7)
#define CR1_RXNEIE (1U<<5)

#define PA3_AF (2 << 6)
#define PA3_AF_USART2_RX (7 << 12)

#define PA2_AF (2 << 4)
#define PA2_AF_USART2_TX (7 << 8)

void rx_init(){
    GPIOA->MODER |= PA3_AF;
    GPIOA->AFR[0] |=  PA3_AF_USART2_RX;

    RCC->APB1ENR |= UART2EN;

    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;

    USART2->CR1 |= CR1_RE;
    USART2->CR1 |= CR1_UE;
}

void rx_interrupt_init(){
    USART2->CR1 |= CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);
}

char rx_read(){
    while(!(USART2->SR & SR_RXNE)){};
	return USART2->DR;
}

void USART2_IRQHandler(void){
	if(USART2->SR & SR_RXNE){
		char key = USART2->DR;
		if(key == 'x'){
			GPIOA->ODR ^= (1U<<5);
		}
	}
}

void tx_init(){
    GPIOA->MODER |= PA2_AF;
    GPIOA->AFR[0] |=  PA2_AF_USART2_TX;

    RCC->APB1ENR |= UART2EN;

    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;

    USART2->CR1 |= CR1_TE;
    USART2->CR1 |= CR1_UE;
}

void tx_send(char c){
    while(!(USART2->SR & SR_TXE)){};
	USART2->DR = c;

}
*/
//--------------

#define BAUDRATE 115200
#define UART2EN (1 << 17)

#define PA2_AF (2 << 4)
#define PA2_AF_USART2_TX (7 << 8)

#define PA3_AF (2 << 6)
#define PA3_AF_USART2_RX (7 << 12)

#define CR1_RE (1 << 2)
#define CR1_TE (1 << 3)
#define CR1_UE (1 << 13)

#define SR_RXNE (1U<<5)
#define SR_TXE (1U<<7)
#define CR1_RXNEIE (1U<<5)

//dma1 usart2 rx = stream 5 channel 4
//dma1 usart2 tx = stream 6 channel 4

#define DMA_STREAM5_CHANNEL4 (4 << 25)
#define DMA_STREAM6_CHANNEL4 (4 << 25)

//https://vivonomicon.com/2019/07/05/bare-metal-stm32-programming-part-9-dma-megamix/

void uart_dma_init(){
    GPIOA->MODER |= PA3_AF | PA2_AF;
    GPIOA->AFR[0] |=  PA3_AF_USART2_RX | PA2_AF_USART2_TX;

    RCC->APB1ENR |= UART2EN;
    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;

    USART2->CR1 |= CR1_RE | CR1_TE | CR1_UE;

    DMA1_Stream6->CR |= DMA_STREAM5_CHANNEL4;

}

void tx_send(char c){
    while(!(USART2->SR & SR_TXE)){};
	USART2->DR = c;
}