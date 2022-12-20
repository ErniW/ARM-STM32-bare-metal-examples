#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include<stdio.h>
#include<string.h>

#include "pll.h"
#include "sysTick.h"
#include "serial.h"
#include "adc.h"
#include "i2c.h"

#define MPU6050_ADDRESS 0x68
#define RESET           0x6B
#define ACCEL_CONFIG    0x1C
#define GYRO_CONFIG     0x1B
#define READ_ACCEL      0x3B
#define READ_GYRO       0x43

int main(){
    clockSpeed_PLL();
    SysTick_Init();

    tx_init();
    i2c_Init();

    i2c_Write(MPU6050_ADDRESS, RESET, 1, 0x00);
    i2c_Write(MPU6050_ADDRESS, ACCEL_CONFIG, 1, 0x00);
    i2c_Write(MPU6050_ADDRESS, GYRO_CONFIG, 1, 0x00);

    while(1){
        char accelData[6];
        char gyroData[6];

        i2c_Read(MPU6050_ADDRESS, READ_ACCEL, 6, (char*)accelData);

        int16_t ax = (accelData[0]<<8 | accelData[1]);
        int16_t ay = (accelData[2]<<8 | accelData[3]);
        int16_t az = (accelData[4]<<8 | accelData[5]);

        i2c_Read(MPU6050_ADDRESS, READ_GYRO, 6, (char*)gyroData);

        int16_t gx = (gyroData[0]<<8 | gyroData[1]);
        int16_t gy = (gyroData[2]<<8 | gyroData[3]);
        int16_t gz = (gyroData[4]<<8 | gyroData[5]);

        printf("Acc: %d, %d, %d Gyro: %d, %d, %d\n", ax, ay, az, gx, gy, gz);
        delay_ms(50);
    };
}

int __io_putchar(int ch){
    tx_send(ch);
    return ch;
}