## MPU6050 I2C
**TODO: create  readme**

### CCR config:

`CCR = ( T_r(scl) + T_w(sclh) ) / T_pclk1 = 225`

From table 61. I2C characteristics
- T_r(scl): 1000 ns
- T_w(sclh): 4000 ns
- T_pclk1 = 1 / 45 MHz = 22.222 ns (from i2c CR2)

### TRISE config:

`TRISE = (T_r(scl) / T_pclk1) + 1 = 46`