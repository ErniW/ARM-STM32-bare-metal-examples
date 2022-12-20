#pragma once

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

void adc_init();
void adc_int_init();
void adc_init_two();
void adc_start_conversion();

uint32_t adc_read();
uint32_t adc_read_channel(uint8_t channel);

void adc_dma_init();
void adc_dma_config(uint32_t peripheral, uint32_t memory, uint16_t size);

void adc_watchdog(int low, int high);