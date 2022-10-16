## Using PWM to fade in and out.
*This example replicates the behavior of Arduino analogWrite function by setting the value range to 255. Of course we aren't limited to that so we can set, for example, 16-bit 65536 resolution.*

`PA5` is set to alternate function.
`CCMR1` is set to PWM mode 1.