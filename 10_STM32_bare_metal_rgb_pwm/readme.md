## Multi-channel PWM and RGB LED
*Example of using three channels within a single timer to fade in and out RGB LED in white color.*

1. Connect the RGB LED to ports `PA8`, `PA9` and `PA10` so we can set **Timer 1** PWM channels 1,2 and 3.
2. Alternate Function of each port must be set to **AF2**.
3. Each channel is set to PWM mode 1.