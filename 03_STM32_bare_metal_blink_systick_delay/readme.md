## Systick counter and delay
Using ARM internal system timer to create a delay.

*The systick is actually a part of CMSIS core not STM32. You can read the CMSIS documentation for Cortex-M4 here: https://arm-software.github.io/CMSIS_5/Core/html/index.html*

According to documentation we have to set the `CLKSOURCE`, `TICKINT` and `ENABLE` bits in **SysTick->CTRL** register.