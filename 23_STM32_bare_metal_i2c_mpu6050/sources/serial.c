#include "serial.h"
#include "pll.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#define BAUDRATE         115200

#define PA2_AF           (2 << 4)
#define PA2_AF_USART2_TX (7 << 8)

#define PA3_AF           (2 << 6)
#define PA3_AF_USART2_RX (7 << 12)

#define DMA_STREAM5_CLEAR_INT ((1 << 6) | (15 << 8))
#define DMA_STREAM6_CLEAR_INT ((1 << 16) | (15 << 18))

#define DMA_STREAM5_CHANNEL4 (4 << 25)
#define DMA_STREAM6_CHANNEL4 (4 << 25)

#define DMA_MEMORY_TO_PERIPHERAL (1 <<6)
#define DMA_PERIPHERAL_TO_MEMORY (3 <<6)

void rx_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    GPIOA->MODER |= PA3_AF;
    GPIOA->AFR[0] |= PA3_AF_USART2_RX;
    
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;
    USART2->CR1 |= USART_CR1_RE | USART_CR1_UE;
}

void rx_interrupt_init(){
    USART2->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART2_IRQn);
}

char rx_read(){
    while(!(USART2->SR & USART_SR_RXNE)){};
    return USART2->DR;
}

void tx_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    GPIOA->MODER |= PA2_AF;
    GPIOA->AFR[0] |= PA2_AF_USART2_TX;

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;
    USART2->CR1 |= USART_CR1_TE | USART_CR1_UE;
}

void tx_send(char c){
    while(!(USART2->SR & USART_SR_TXE)){};
    USART2->DR = (c & 0xFF);
};

void tx_dma_init(unsigned int buffer, unsigned int destination, int size){
    
    __disable_irq();

    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    DMA1->HIFCR = DMA_STREAM6_CLEAR_INT; 

    DMA1_Stream6->CR &=~ DMA_SxCR_EN;
    while (DMA1_Stream6->CR & DMA_SxCR_EN) {};

    DMA1_Stream6->CR |= DMA_STREAM6_CHANNEL4 | DMA_MEMORY_TO_PERIPHERAL;
    DMA1_Stream6->CR |= DMA_SxCR_MINC | DMA_SxCR_DMEIE | DMA_SxCR_TEIE | DMA_SxCR_TCIE;
    
    DMA1_Stream6->PAR = destination;
    DMA1_Stream6->M0AR = buffer;
    DMA1_Stream6->NDTR = size;
    
    DMA1_Stream6->CR |= DMA_SxCR_EN;
    USART2->CR3 |= USART_CR3_DMAT;

    NVIC_EnableIRQ(DMA1_Stream6_IRQn); 

    __enable_irq(); 
};

void rx_dma_init(uint32_t buffer, uint32_t destination, int size){

    __disable_irq();

    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    DMA1->HIFCR = DMA_STREAM5_CLEAR_INT; 

    DMA1_Stream5->CR &=~ DMA_SxCR_EN;
    while (DMA1_Stream5->CR & DMA_SxCR_EN) {};

    DMA1_Stream5->CR |= DMA_STREAM5_CHANNEL4;
    DMA1_Stream5->CR |= DMA_SxCR_MINC | DMA_SxCR_DMEIE | DMA_SxCR_TEIE | DMA_SxCR_TCIE;
    DMA1_Stream5->CR &=~ DMA_PERIPHERAL_TO_MEMORY;

    DMA1_Stream5->PAR = destination;
    DMA1_Stream5->M0AR = buffer;
    DMA1_Stream5->NDTR = size;

    DMA1_Stream5->CR |= DMA_SxCR_EN;
    USART2->CR3 |= USART_CR3_DMAR;

    NVIC_EnableIRQ(DMA1_Stream5_IRQn); 

    __enable_irq(); 
};

void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_TC){     
        USART2->SR &=~ USART_SR_TC;
    }
}