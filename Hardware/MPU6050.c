#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050Reg.h"

#include "math.h"
#define MPU_ADDRESS  0xD0

#define _M_PI 57.2958

void MPU_WriteReg(uint8_t Address, uint8_t data){  
	MyI2C_Start();																	
	MyI2C_SendByte(MPU_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Address);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}
uint8_t MPU_ReadReg(uint8_t Address){	
	uint8_t data;
	MyI2C_Start();
	MyI2C_SendByte(MPU_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Address);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU_ADDRESS | 0x01);
	MyI2C_ReceiveAck();
	data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	return data;
}

void MPU6050_Init(){
	MyI2C_Init();

	MPU_WriteReg(MPU6050_PWR_MGMT_1, 0x00);
	MPU_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU_WriteReg(MPU6050_SMPLRT_DIV, 0x07);
	MPU_WriteReg(MPU6050_CONFIG, 0x03);
	MPU_WriteReg(MPU6050_ACCEL_CONFIG, 0x00);
	MPU_WriteReg(MPU6050_GYRO_CONFIG, 0x00);
	
}

uint8_t Get_Gravity(){
	int16_t AccX, AccY;
	uint8_t Gravity_Direction;
	uint8_t High, Low;
	High = MPU_ReadReg(MPU6050_ACCEL_XOUT_H);
	Low = MPU_ReadReg(MPU6050_ACCEL_XOUT_L);
	AccX = (High << 8) | Low;
	
	High = MPU_ReadReg(MPU6050_ACCEL_YOUT_H);
	Low = MPU_ReadReg(MPU6050_ACCEL_YOUT_L);
	AccY = (High << 8) | Low;

  double degrees = atan2(AccX, AccY) * (_M_PI);
	
	if(degrees > -112.5 && degrees <= -67.5){
		Gravity_Direction = 0;//down
	}
	else if(degrees > -157.5 && degrees <= -112.5){
		Gravity_Direction = 1;//down_left
	}
	else if(degrees > -67.5 && degrees <= -22.5){
		Gravity_Direction = 2;//down_right
	}
	else if(degrees > 67.5 && degrees <= 112.5){
		Gravity_Direction = 3;//above
	}
	else if(degrees > 22.5 && degrees <= 67.5){
		Gravity_Direction = 4;//above_left
	}
	else if(degrees > 112.5 && degrees <= 157.5){
		Gravity_Direction = 5;//above_right
	}
	else if(degrees > 157.5 || degrees <= -157.5){
		Gravity_Direction = 6;//left
	}
	else if(degrees > -22.5 && degrees <= 22.5){
		Gravity_Direction = 7;//right
	}
	return Gravity_Direction;
}
