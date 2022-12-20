#pragma once

void i2c_Init();
void i2c_Read(char saddr, char maddr, int n, char* data);
void i2c_Write(char saddr, char maddr, int n, char* data);