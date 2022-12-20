#pragma once

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

void rx_init();
void rx_interrupt_init();
char rx_read();

void tx_init();
void tx_send(char c);

void tx_dma_init(unsigned int buffer, unsigned int destination, int size);
void rx_dma_init(uint32_t buffer, uint32_t destination, int size);