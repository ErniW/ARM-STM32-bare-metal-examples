## Basic blink example
1. The port pin A5 with the build-in LED exists in AHB1 bus register. You can see that in block diagram on page 16 of *STM32F446xC/E* datasheet. To activate the bus enable the `AHB1ENR`.
2. To set the pin to output set the 10th bit in `GPIOA` port *GPIO port mode register (7.4.1)* `MODER`. Each pin has two bits to configure them.
3. We're toggling the LED in *GPIO port output data register (7.4.6)*. The 5th pin correspond to 5th bit in that register.
4. You can achieve similar result via *GPIO port bit set/reset register (7.4.7)* `BSRR` in which the low 16 bits are setting the bit and higher 16 bits reseting them.
5. The delay is a for loop just for demo purpose, later we will use more precise timing. I'm using the dull `nop` assembly instruction. You could delete it but set the `int i` to `volatile int i` to prevent optimization.