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
//https://vivonomicon.com/2019/07/05/bare-metal-stm32-programming-part-9-dma-megamix/

#define DMA_STREAM5_CHANNEL4 (4 << 25)
#define DMA_STREAM6_CHANNEL4 (4 << 25)
#define ENABLE_DMA1 (1 << 21)
#define DMA_STREAM_EN 1
#define DMA_STREAM6_CLEAR_INT ((1 << 16) | (15 << 18))
#define DMA_STREAM5_CLEAR_INT ((1 << 6) | (15 << 8))

#define DMA_MINC_INC (1 << 10)
#define DMA_MEMORY_TO_PERIPHERAL (1 <<6)
#define DMA_PERIPHERAL_TO_MEMORY (3 <<6)
#define DMA_DMEIE (1 << 1)
#define DMA_TEIE (1 << 2)
#define DMA_TCIE (1 << 4)

#define UART_DMAT_EN (1 << 7)
#define UART_DMAR_EN (1 << 6)

#define TXEIE (1 << 7)
#define GPIOA_EN (1 << 0)
#define TRANSFER_COMPLETE_FLAG (1 << 6)
#define TCIE (1 << 6)

#define IDLEIE (1 << 4)

void uart_tx_init(){
    RCC->AHB1ENR |= GPIOA_EN; 
    RCC->APB1ENR |= UART2EN;

    GPIOA->AFR[0] |= PA2_AF_USART2_TX;
    GPIOA->MODER |= PA2_AF;

    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U)) / BAUDRATE;
    USART2->CR1 |= TCIE | CR1_TE | CR1_UE;

    USART2->SR =~ TRANSFER_COMPLETE_FLAG;
    NVIC_EnableIRQ(USART2_IRQn);   
}

void uart_rx_init(){
    RCC->AHB1ENR |= GPIOA_EN; 
    RCC->APB1ENR |= UART2EN;

    GPIOA->MODER |= PA3_AF;
    GPIOA->AFR[0] |=  PA3_AF_USART2_RX;

    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;
    USART2->CR1 |=  CR1_RXNEIE | CR1_RE | CR1_UE;

    NVIC_EnableIRQ(USART2_IRQn);
}

void uart_rx_dma_init(uint32_t buffer, uint32_t destination, int size){
    RCC->AHB1ENR |= ENABLE_DMA1;
    DMA1->HIFCR = DMA_STREAM5_CLEAR_INT; 

    DMA1_Stream5->CR &=~ DMA_STREAM_EN;
    while (DMA1_Stream5->CR & DMA_STREAM_EN) {};

    DMA1_Stream5->PAR = destination;
    DMA1_Stream5->M0AR = buffer;
    DMA1_Stream5->NDTR = size;

    DMA1_Stream5->CR |= DMA_STREAM5_CHANNEL4;
    DMA1_Stream5->CR |= DMA_MINC_INC | DMA_DMEIE | DMA_TEIE | DMA_TCIE;
    DMA1_Stream5->CR &=~ DMA_PERIPHERAL_TO_MEMORY;
    DMA1_Stream5->CR |= DMA_STREAM_EN;

    USART2->CR3 |= UART_DMAR_EN;
     NVIC_EnableIRQ(DMA1_Stream5_IRQn); 

    // RCC->AHB1ENR |= ENABLE_DMA1;
    // DMA1->HIFCR = DMA_STREAM6_CLEAR_INT; 

    // DMA1_Stream6->CR &=~ DMA_STREAM_EN;
    // while (DMA1_Stream6->CR & DMA_STREAM_EN) {};

    // DMA1_Stream6->PAR = destination;
    // DMA1_Stream6->M0AR = buffer;
    // DMA1_Stream6->NDTR = size;

    // DMA1_Stream6->CR |= DMA_STREAM6_CHANNEL4;
    // DMA1_Stream6->CR |= DMA_MINC_INC | DMA_MEMORY_TO_PERIPHERAL | DMA_DMEIE | DMA_TEIE | DMA_TCIE;
    // DMA1_Stream6->CR |= DMA_STREAM_EN;

    // USART2->CR3 |= UART_DMAT_EN;

    // NVIC_EnableIRQ(DMA1_Stream6_IRQn);  
}

void uart_tx_dma_init(unsigned int buffer, unsigned int destination, int size){

    RCC->AHB1ENR |= ENABLE_DMA1;
    DMA1->HIFCR = DMA_STREAM6_CLEAR_INT; 

    DMA1_Stream6->CR &=~ DMA_STREAM_EN;
    while (DMA1_Stream6->CR & DMA_STREAM_EN) {};

    DMA1_Stream6->PAR = destination;
    DMA1_Stream6->M0AR = buffer;
    DMA1_Stream6->NDTR = size;

    DMA1_Stream6->CR |= DMA_STREAM6_CHANNEL4;
    DMA1_Stream6->CR |= DMA_MINC_INC | DMA_MEMORY_TO_PERIPHERAL | DMA_DMEIE | DMA_TEIE | DMA_TCIE;
    DMA1_Stream6->CR |= DMA_STREAM_EN;

    USART2->CR3 |= UART_DMAT_EN;

    NVIC_EnableIRQ(DMA1_Stream6_IRQn);    
}

void tx_send(char c){
    while(!(USART2->SR & SR_TXE)){};
	USART2->DR = c;

}