#pragma once

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

void SysTick_Init();
void SysTick_Handler();
void delay_ms(uint32_t ms);
uint32_t getMillis();
