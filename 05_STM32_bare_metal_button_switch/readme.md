## Button
STM32 Nucleo boards have build-in button located in port C pin 13 (`PC13`).

*We don't need to set the pin to input because it's the pin default mode.*

To read pin state, check **GPIO port input data register** `GPIOC->IDR` (chapter 7.4.5).