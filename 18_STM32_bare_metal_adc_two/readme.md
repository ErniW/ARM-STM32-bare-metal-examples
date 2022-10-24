## ADC Polling
Connect two potentiometers in ports `PA0` and `PA1`.

**Polling is the least efficient way to read from several channels. It starts the conversion, reads the value blocking everything in-between and eventually move into next one. In next two examples I will show how to use more advanced features for non-blocking multi-channel measurements.**

*I thought it's easy. But it's not.*

Generally, to read multiple channels we need to set a query in `SQR` registers. Staring from zero, for each conversion we need to set the channel in that queue. The data register is set and immediately released after finishing measurements so without using DMA (Direct Memory Access) with scan mode or Injected Group,we can't read the values. Based on what I've searched on the internet - interrupts can't handle steps between measurments without some advanced programming using timers. *Maybe I'm wrong on that, if so, please correct me.*

### Why my ADC readings affect each other even if I'm using the polling method?

It occurs when CPU clock, or rather ADC clock which is too fast. It is possible to fix that from hardware side, but from software we can set the ADC clock prescaler `ADCPRE` to /8. 

**Explanation of ADC on STM32 can be found here:**
https://www.st.com/resource/en/application_note/an3116-stm32s-adc-modes-and-their-applications-stmicroelectronics.pdf