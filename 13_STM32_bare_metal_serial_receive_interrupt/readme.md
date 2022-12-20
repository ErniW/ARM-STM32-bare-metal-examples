## Serial receive interrupt
The only difference is enabling the interrupt:

    USART2->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);

After that include `USART2_IRQHandler` which will toggle the LED when "x" is received.