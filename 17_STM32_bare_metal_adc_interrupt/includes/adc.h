#pragma once

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

void adc_init();
void adc_start_conversion();
uint32_t adc_read();