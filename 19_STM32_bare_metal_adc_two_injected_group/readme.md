## ADC injected group
Connect two potentiometers in ports `PA0` and `PA1`.

**Injected group allows to read 4 channels at once in non-blocking way. When conversion is finished, an interrupt occurs. Better than polling but still worse than DMA.**



**Explanation of ADC on STM32 can be found here:**
https://www.st.com/resource/en/application_note/an3116-stm32s-adc-modes-and-their-applications-stmicroelectronics.pdf