#include "serial.h"
#include "pll.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#define BAUDRATE 115200

#define SR_RXNE (1U<<5)
#define UART2EN (1U<<17)
#define CR1_RE (1U<<2)
#define CR1_UE (1U<<13)

#define PA3_AF (2 << 6)
#define PA3_AF_USART2_RX (7 << 12)

void rx_init(){
    GPIOA->MODER |= PA3_AF;
    GPIOA->AFR[0] |=  PA3_AF_USART2_RX;

    RCC->APB1ENR |= UART2EN;

    USART2->BRR = (APB1_FREQ + (BAUDRATE/2U))/BAUDRATE;

    USART2->CR1 |= CR1_RE;
    USART2->CR1 |= CR1_UE;
}

char rx_read(){
    while(!(USART2->SR & SR_RXNE)){};
	return USART2->DR;
}