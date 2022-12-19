## Timers
*Instead of SysTick internal timer we will use STM32 peripheral timers. Later we will use it to fade in and out LED and control servo via PWM.*

*ARM architecture provides more timers and more features than AVR. I will stick to the basics similarly to my AVR examples.*

To create a simple 1 second blink we can create a timer with frequency of 1 Hz.

### How to enable the timer for PA5:

1. Enable timer on `APB1` bus. To check which timer is bound to `PA5` LED we need to read the **Table 11. Alternate function** in **STM32F446xC/E** manual. We can use **Timer 2 channel 1**. Set the `TIM2EN` in `APB1ENR`. 

2. Usually to enable alternate functions of pin we set its mode to **Alternate function mode** in **GPIO port mode register** with bit value `10`. But in this case its not necessary as we use that pin as output for our LED.

3. We need to specify which alternate function to use. Our timer according to the alternate function table is `AF1`. Enable it in **GPIO alternate function low register**.

### How to set the timer frequency so we can measure 1 second interval:

1. To properly set the prescaler we need to use the *APB1 Timer clock*. According to documentation *(Figure 14. Clock tree)* the rule of its frequency is:

*If ABP1 presc = 1 multiply by 1*
*else multiply by 2*.

Because PLL sets APB1_FREQ to 45MHz, the APB1 prescaler equals 4 therfore our timer frequency equals 90 MHz.

If our prescaler is set to `90000000 / 10000 -> 9000 - 1` it means our clock is set to 10KHz. **So the timer will reach 1 second after `10000` ticks.**

2. Set the `ARR` to 10000-1 so it will reload with each second.

3. Enable the timer in `TIM2->CR1` control register.

4. We can write timer code in our main loop, but I want to use interrupt for that.

    while(!(TIM2->SR & SR_UIF)){}
    TIM2->SR &=~ SR_UIF;
    GPIOA->ODR ^= (1U<<5);

### Timer interrupt.

1. Enable update event interrupt `TIM2->DIER`.
2. Enable `TIM2_IRQn` in NVIC.
3. Now create the `TIM2_IRQHandler`. We have to clear the `TIM_SR_UIF` manually each time this interrupt occurs.

*When setting any interrupt in a function you should `__disable_irq` and `__enable_irq` to be sure it's configured without any interruption. Interrupt-safe code is a huge thing in embedded development.*