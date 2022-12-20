## ADC Direct Memory Access (DMA)
Connect two potentiometers in ports `PA0` and `PA1`.

In short: DMA allows to transfer data (memory to memory, memory to peripheral, peripheral to memory) ommiting the CPU clock and main loop. The data is transferred immediately. It can be used to simplify the transfer for ADC, UART etc. **DMA is necessary for efficient multichannel readings of ADC.**

There are two DMA controllers, each with 8 channels. Mappings can be found in **Table 28. DMA1 request mapping** and **Table 29. DMA2 request mapping**.

1. We are using ADC sequence with continuous mode.
2. ADC is bound to DMA2 stream 0 channel 0.
3. DMA is set to send from peripheral (ADC) to memory (data buffer).

*You should check the documentation to understand all of DMA settings required to make it work.*