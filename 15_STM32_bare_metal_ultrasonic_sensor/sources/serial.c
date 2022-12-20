#include "serial.h"
#include "pll.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#define BAUDRATE         115200

#define PA2_AF           (2 << 4)
#define PA2_AF_USART2_TX (7 << 8)

#define PA3_AF           (2 << 6)
#define PA3_AF_USART2_RX (7 << 12)

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