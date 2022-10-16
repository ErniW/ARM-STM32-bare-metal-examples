## Multi-channel PWM and RGB LED
*Example of using three channels within a single timer to fade in and out RGB LED.*

1. Connect the RGB LED to ports `PA0`, `PA1` and `PA2` so we can set **Timer 5** PWM channels 1,2 and 3. Instead of `pwm_init` I'm using `pwm_rgb_init` function.

2. Alternate Function of each port must be set to **AF2**.

 <!-- Enable channel 1,2 and 3. in `TIM5->EGR`. -->

3. TIM5->CCMR1