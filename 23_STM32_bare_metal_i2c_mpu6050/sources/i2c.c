#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

#include "i2c.h"

//#define I2C_100KHZ 80
#define SD_MODE_MAX_RISE_TIME 17


#define PB8_AF_MODE (1 << 17)
#define PB9_AF_MODE (1 << 19)

#define PB8_AF4_I2C_SCL (1 << 2)
#define PB9_AF4_I2C_SDA (1 << 6)

#define PB8_PULLUP (1 << 16)
#define PB9_PULLUP (1 << 18)

void i2c_Init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    GPIOB->MODER |= PB8_AF_MODE | PB9_AF_MODE;
    GPIOB->OTYPER |= GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9;
    GPIOB->PUPDR |= PB8_PULLUP | PB9_PULLUP;
    GPIOB->AFR[1] |= PB8_AF4_I2C_SCL | PB9_AF4_I2C_SDA;

    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &=~ I2C_CR1_SWRST;

    I2C1->CR2 |= 45;//16;
    I2C1->CCR = 225;//I2C_100KHZ;
    I2C1->TRISE = SD_MODE_MAX_RISE_TIME;
    I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_Read(char saddr, char maddr, int n, char* data){
    volatile int tmp;

    while(I2C1->SR2 & I2C_SR2_BUSY);
    I2C1->CR1 |= I2C_CR1_START;

    while(!(I2C1->SR1 & I2C_SR1_SB));
    I2C1->DR = saddr << 1;

    while(!(I2C1->SR1 & I2C_SR1_ADDR));
    tmp = I2C1->SR2;

    while(!(I2C1->SR1 & I2C_SR1_TXE));
    I2C1->DR = maddr;

    while(!(I2C1->SR1 & I2C_SR1_TXE));
    I2C1->CR1 |= I2C_CR1_START;

    while(!(I2C1->SR1 & I2C_SR1_SB));
    I2C1->DR = saddr << 1 | 1;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    tmp = I2C1->SR2;

    I2C1->CR1 |= I2C_CR1_ACK;

    while(n >0){
        if(n == 1){
            I2C1->CR1 &=~ I2C_CR1_ACK;
            I2C1->CR1 |= I2C_CR1_STOP;

            while (!(I2C1->SR1 & I2C_SR1_RXNE));
            *data++ = I2C1->DR;

            break;
        }
        else{

            while (!(I2C1->SR1 & I2C_SR1_RXNE));
            (*data++) = I2C1->DR;
            n--;
        }
    }
}

void i2c_Write(char saddr, char maddr, int n, char* data){

    volatile int tmp;

    while(I2C1->SR2 & I2C_SR2_BUSY);
    I2C1->CR1 |= I2C_CR1_START;

    while(!(I2C1->SR1 & I2C_SR1_SB));
    I2C1->DR = saddr << 1;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    tmp = I2C1->SR2;

    while(!(I2C1->SR1 & I2C_SR1_TXE));
    I2C1->DR = maddr;

    for (int i=0; i<n; i++){

        while(!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = *data++;
    }

    while(!(I2C1->SR1 & I2C_SR1_BTF));
    I2C1->CR1 |= I2C_CR1_STOP;
}
