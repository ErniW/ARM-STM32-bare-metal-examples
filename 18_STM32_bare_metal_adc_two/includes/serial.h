#pragma once

void rx_init();
void rx_interrupt_init();
char rx_read();

void tx_init();
void tx_send(char c);