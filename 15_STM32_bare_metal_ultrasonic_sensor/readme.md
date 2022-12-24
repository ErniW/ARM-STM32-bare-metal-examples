## HC-SR04
**The code provides two versions: blocking and non-blocking with interrupts (because many things can be done meanwhile). Later it could use additional timer to automatically check for new value instead of measuring time interval with getMillis.**

Connect the `Trig` Pin to `PA8` and `Echo` to `PA9`.

### How ultrasonic sensor works:
1. Send 10us ultrasonic pulse through Trig pin.
2. Wait until the pulse returns. 
3. Echo pin returns high signal corresponding to time of flight. 
4. We can compute the distance according to formula `duration * speed of sound / 2`. *Remember to use correct units!*

### Timer requirements:
- Timing should be done at microseconds scale. So setting prescaler to `180 - 1` will make our timer work at **1Mhz frequency and a period of 1us.** *It's 180 and not 90 because of formula mentioned in one of previous timer examples.*
- To read the length of received pulse, set Timer channel as input. *The same method can be used to measure length of a button press.*
- We can set another channel to measure 10us and send the Trigger pulse.

### Interrupts:
For each measurements, we actually need four interrupts to happen:
1. Start the Trig pulse. Count 10us to stop the signal.
2. Measure the timestamp of rising edge when our returning signal on Echo pin.
3. Measure another timestamp of falling edge, substract them to eventually get the distance. *Theoretically you can set a PWM input measurement.*
4. Return 0 when overflow occurs. *TODO: Better handling of timeouts*

*In this example we are using `__io_putchar` to send chars with printf function.* **Please notice that using printf inside interrupts is not a good option,it's non-reentrant and not thread-safe.**
