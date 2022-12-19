## Using PWM to fade in and out.
*Fades in and out our LED. In the servo example we will use more precise control of PWM to define exact parameters.*

1. `PA5` is set to alternate function mode in `MODER` register.
2. **The LED is bound to Timer 2 channel 1 on alternate function 1.** *Read the Alternate Function Table for reference (it's not in register documentation - check homepage of repository).*
3. `CCMR1` is set to PWM mode 1.
4. In `ARR` we set the actual period while `CCR1` is responsible for pulse width. The duty cycle can be calculated as a percentage of `CCR1` related to `ARR`.
