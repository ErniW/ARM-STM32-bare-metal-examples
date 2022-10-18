## Serial receive
*Receive a single char to trigger anything.*

### Enable the USART:
1. The STM32 Nucleo boards are connected to computer via **USART2**. To enable it, set `PA3` to alternate function **USART2_RX**.
2. Enable **UART2** in `APB1ENR`.
3. After setting the baudrate enable **USART** with `UE` bit and receiver with `RE` bits.

### Set the baudrate:
To set the baudrate we need to calculate the equation:
`APB1_CLK+(BAUDRATE/2U) / BAUDRATE`
and place it into `USART2->BRR` register.

### Read a single char:
I wrote a simple `rx_read` function which listens for incoming data and returns the buffer from data register.

*You can see the LED turning on when writing "A" char via serial port, and turning off when "B" is received. This example is not convenient as it blocks the execution of code. In the next example I will use interrupt to create a non-blocking receiver.*

*To work with Serial monitor you can open Arduino IDE Serial Monitor or install other software.*