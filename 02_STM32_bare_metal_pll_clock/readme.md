## Configuring the CPU clock to 180Mhz via PLL
By default, the STM32 boards are set to 16Mhz provided via internal HSI clock. To configure the board to run at 180 Mhz we need to use something called *phase-locked loop* (PLL).

*The PLL input can be supplied from internal HSI or external HSE clocks (HSE can be significantly more accurate). Unfortunately, STM32 Nucleo board doesn't have external clock. You can solder it on your own.*

*The STM32 Cube IDE automates this configuration, otherwise it can be tricky to do correctly. You can see how the IDE handles the parameters and then you can adapt to your needs (by rewriting it to bare-metal C).*

### Things we need to configure:
1. Enable HSI.
2. Set `PLL` input to HSI.
3. In `RCC->PLLCFGR` set `PLL_M` prescalar to /8
4. Set `PLL_N` multiplier to x180
5. Set `PLL_P` prescalar to /2
6. Set `PLL_Q` prescalar to /2 (not necessary for now)
7. In `RCC->CFGR` do not divide `sysclk`.
8. Divide `APB2` by 2 (max is 90Mhz) by using `RCC_CFGR_PPRE2_DIV2` macro.
9. Divide `APB1` by 4 (max is 45Mhz) by using `RCC_CFGR_PPRE1_DIV4` macro.
10. Enable the PLL.
11. Over drive the power in `PWR->CR` for increased power consumption.
12. In `FLASH->ACR` we need to set the latency of flash memory so it can keep up with the increased CPU clock (flash memory can run up to 30 Mhz).
13. Switch the system clock to PLL.

**From the PLL frequency equation we have our desired clock frequency:**
`F_PLL = (16000000 * (180 / 8)) / 2 = 180000000 Hz = 180Mhz`

After all of these steps you can compare the increased blinking speed using the same for loop. It executes each cycle much faster (approx. 11x).