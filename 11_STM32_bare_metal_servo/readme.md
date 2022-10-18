## Servo
*Control the SG-90 servo via PWM signal with different period.*

### SG-90 servo control parameters:
- **Frequency: 50Hz**
- **Period: (related to frequency): 20ms.**
- **Pulse width: 0.5 - 2.5ms.** *It's not 1-2 ms (a commonly used range for all servos), many people didn't even bother to check that posting their tutorials or code snippets. Always check the specs of your servo.*

### Angle/Period relation:
- Angle 0 should be 0.5ms.
- Angle 90 should be 1.5ms.
- Angle 180 should be 2.5ms.

### Calculating the correct timer frequency:
Our Timer clock frequency is equal to 90MHz. To set it to 50Hz we must set correct prescaler. Before that, connect Servo signal pin to `PA5` which is bound to **Timer 2 Channel 1.**

1. Set the `PA5` mode to Alternate Function in `MODER` register and enable Timer 2 channel 1 in **Alternate Function Register**. Remember to enable `AHB1` and `APB1` buses.
2. Set the prescaler to `90 - 1` so the timer frequency is now 1 MHz.
3. `TIM2->ARR` is responsible for wave frequency. It reloads the counter when a certain amount of clock ticks occur. `1Mhz / 20000Hz = 50Hz`. The period equals 20ms.
4. *You can use PWM duty cycle equation to calculate the percentage of period, however I'm just hardcoding values that corresponds to angle 0, 90 and 180.*
5. *Because of Servo's physicality, we need to give it some time to move into desired position.*

*While servo is moving you can see the build-in LED changing its brightness.*