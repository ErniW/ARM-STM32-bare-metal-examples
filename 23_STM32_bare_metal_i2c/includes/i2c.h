#pragma once

void i2cInit();
void i2cRead(char saddr, char maddr, int n, char* data);
void i2cWrite(char saddr, char maddr, int n, char* data);