## Button Interrupt
*While reading this you should already be familiar what interrupts are. I'm not covering the very basics of embedded programming. If you search for more basic guide check my AVR bare metal examples repository.*

### How to enable interrupt on STM32 build-in button?
1. You can see that **SYSCFG external interrupt configuration register 3** enables `EXTI13` interrupt for pin 13. It's important to understand that **this interrupt is bound to each pin 13 of each port.** Because only one port can access it at once, we need to specify which port to use. To use port C set `EXTI13` to `0010`.

*`EXTICR[3]` is register 4 (we start counting from 0).*

2. `EXTI->FTSR` sets the interrupt to falling edge.

3. The `EXTI15_10_IRQn` and `EXTI15_10_IRQHandler` are specified in included STM32 system files. The `EXTI15_10_IRQHandler` is responsible for external interrupts 10-15. When its triggered we need to check which pin triggered the interrupt, and clear its flag. *(Correct me if I'm wrong)*