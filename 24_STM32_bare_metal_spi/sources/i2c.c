#include "i2c.h"

#include "../../STM32F446RE/stm32f4xx.h"
#include "../../STM32F446RE/stm32f446xx.h"

/*
 * PB8 I2C1_SCL
 * PB9 I2C1_SDA
 *
 * AF4
 */

#define I2C_100KHZ 80
#define SD_MODE_MAX_RISE_TIME 17
#define CR1_PE (1U<<0)

#define SR2_BUSY (1U<<1)
#define CR1_START (1U<<8)
#define SR1_SB (1U<<0)
#define SR1_ADDR (1U<<1)
#define SR1_TXE (1U<<7)
#define CR1_ACK (1U<<10)
#define CR1_STOP (1U<<9)
#define SR1_RXNE (1U<<6)
#define SR1_BTF (1U<<2)

void i2cInit(){
	RCC->AHB1ENR |= (1U<<1);
	RCC->APB1ENR |= (1U<<21);

	GPIOB->MODER &=~ (1U<<16);
	GPIOB->MODER |= (1U<<17);
	GPIOB->MODER &=~ (1U<<18);
	GPIOB->MODER |= (1U<<19);

	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);

	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR  &=~ (1U<<17);
	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR  &=~ (1U<<19);

	GPIOB->AFR[1] &=~ (1U<<0);
	GPIOB->AFR[1] &=~ (1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &=~ (1U<<3);

	GPIOB->AFR[1] &=~ (1U<<4);
	GPIOB->AFR[1] &=~ (1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~ (1U<<7);

	//enter reset mode
	I2C1->CR1 |= (1U<<15);

	//come out of reset mode
	I2C1->CR1 &=~ (1U<<15);

	//set peripheral to 16 mhz clock
	I2C1->CR2 = (1U<<4);

	//set i2c to standard mode
	I2C1->CCR = I2C_100KHZ;

	//set rise time
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

	//enable I2C1 module
	I2C1->CR1 |= CR1_PE;
}

void i2cRead(char saddr, char maddr, int n, char* data){
	volatile int tmp;

	//wait until bus not busy
	while(I2C1->SR2 & (SR2_BUSY)){}

	//generate start
	I2C1->CR1 |= CR1_START;

	//wait until start flag is set
	while(!(I2C1->SR1 & ((SR1_SB)))){}

	//transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait until addr flag is set
	while (!(I2C1->SR1 & (SR1_ADDR))){}

	//clear addr flag
	tmp = I2C1->SR2;

	//wait until transmitter is empty
	while(!(I2C1->SR1 & SR1_TXE)){}

	//send memory address
	I2C1->DR = maddr;

	//wait until transmitter is empty
	while(!(I2C1->SR1 & SR1_TXE)){}

	//generate restart
	I2C1->CR1 |= CR1_START;

	//wait until start flag is set
	while(!(I2C1->SR1 & SR1_SB)){}

	//Transmit slave address + read
	I2C1->DR = saddr << 1 | 1;

	//wait until addr flag is set
	while (!(I2C1->SR1 & (SR1_ADDR))){}

	//clear addr flag
	tmp = I2C1->SR2;

	//Enable acknowledge
	I2C1->CR1 |= CR1_ACK;

	while(n >0U){
		//check if one byte
		if(n == 1U){

			//disable acknowledge
			I2C1->CR1 &=~ CR1_ACK;

			//generate stop condition
			I2C1->CR1 |= CR1_STOP;

			//wait until rxne flag is set
			while (!(I2C1->SR1 & SR1_RXNE)){}

			*data++ = I2C1->DR;

			break;
		}
		else{
			//wait until rxne flag is set
			while (!(I2C1->SR1 & SR1_RXNE)){}

			(*data++) = I2C1->DR;

			n--;
		}
	}
}

void i2cWrite(char saddr, char maddr, int n, char* data){

	volatile int tmp;


	//wait until bus not busy
	while(I2C1->SR2 & (SR2_BUSY)){}

	//generate start
	I2C1->CR1 |= CR1_START;

	//wait until start flag is set
	while(!(I2C1->SR1 & ((SR1_SB)))){}

	//transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait until addr flag is set
	while (!(I2C1->SR1 & (SR1_ADDR))){}

	//clear addr flag
	tmp = I2C1->SR2;

	//wait until transmitter is empty
	while(!(I2C1->SR1 & SR1_TXE)){}

	//send memory address
	I2C1->DR = maddr;

	for (int i=0; i<n; i++){

		while(!(I2C1->SR1 & SR1_TXE)){}

		//transmit memory address
		I2C1->DR = *data++;
	}

	while(!(I2C1->SR1 & (SR1_BTF))){}


	//generate stop after data received
	I2C1->CR1 |= CR1_STOP;
}
