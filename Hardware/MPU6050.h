#ifndef __MPU6050_H
#define __MPU6050_H


void MPU6050_Init();
void MPU_WriteReg(uint8_t Address, uint8_t data);
uint8_t MPU_ReadReg(uint8_t Address);
 int8_t Get_Gravity();

#endif

