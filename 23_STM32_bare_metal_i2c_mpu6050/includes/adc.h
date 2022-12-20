#pragma once

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

void adc_init();
void adc_init_two();
void adc_start_conversion();

uint32_t adc_read_value(uint8_t channel);

uint32_t adc_read();

void adc_start();
void adc_dma_init();
void dma_config(uint32_t srcAdd, uint32_t destAdd, uint16_t size);
void adc_watchdog();