## ADC
Connect the potentiometer to port `PA0` which is equivalent of Arduino pin A0.

*Important: connect power source to 3V. Otherwise the value will overflow.*

### Enabling the ADC:
1. Set `PA0` to analog input.
2. Enable `ADC1` in `APB2ENR` register.
3. Define the conversion sequence on adc channel 1 and set the sequence length to 1 (because we measure one sensor).
4. Start conversion in continuous conversion mode.
5. Read data from `ADC1->DR` data register when conversion is finished.

We are using printf to send the value, to make it work we need to include `__io_putchar` function and include `syscalls.c` from STM32F446RE directory, the file was autogenerated by STM32 IDE.