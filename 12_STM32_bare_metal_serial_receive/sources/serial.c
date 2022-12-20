#include "serial.h"
#include "pll.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#define BAUDRATE            115200
#define PA3_AF              (2 << 6)
#define PA3_AF_USART2_RX    (7 << 12)

void rx_init(){
    GPIOA->MODER |= PA3_AF;
    GPIOA->AFR[0] |=  PA3_AF_USART2_RX;
    
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;
    USART2->CR1 |=  USART_CR1_RE | USART_CR1_UE;
}

char rx_read(){
    while(!(USART2->SR & USART_SR_RXNE)){};
    return USART2->DR;
}