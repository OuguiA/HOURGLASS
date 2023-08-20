#include "stm32f10x.h"                  // Device header
#include "MySpi.h"

void Max7219_x_WriteByte(uint8_t Address, uint8_t byte, uint8_t x){
		SPI_Start();
		SPI_SwapByte(Address);
		SPI_SwapByte(byte);
		uint8_t i;
		for(i = 1; i < x; i++){
			SPI_W_SCK(1);
			SPI_SwapByte(0x00);
			SPI_SwapByte(0x00);
		}
		SPI_Stop();
		for(i = x; i < 7; i++){
			SPI_SwapByte(0x00);
			SPI_SwapByte(0x00);
		}
		
 }

void Max7219_Init(void) {
	 MySpi_Init();
	 for(int i = 1; i <= 8; i++){
		 Max7219_x_WriteByte(0x09, 0x00, i);       //���뷽ʽ��BCD��
		 Max7219_x_WriteByte(0x0a, 0x0D, i);       //���� 
		 Max7219_x_WriteByte(0x0b, 0x07, i);       //ɨ����ޣ�8���������ʾ
		 Max7219_x_WriteByte(0x0c, 0x01, i);       //����ģʽ��0����ͨģʽ��1
		 Max7219_x_WriteByte(0x0f, 0x00, i);  		 //��ʾ���ԣ�1�����Խ�����������ʾ��0
	 }
}

void Max7219_1_Scan(uint8_t * Matrix){
	for(uint8_t i = 1; i <= 8; i++){
			Max7219_x_WriteByte(i,Matrix[i],1);     
		}
}
void Max7219_2_Scan(uint8_t * Matrix){
	for(uint8_t i = 1; i <= 8; i++){
			Max7219_x_WriteByte(i,Matrix[i],2);
		}
}

void Max7219_OpenXY(uint8_t x, uint8_t y, uint8_t *Matrix){
	uint8_t value = 1 << (y - 1);
	Matrix[x] |= value;
} 
void Max7219_CloseXY(uint8_t x, uint8_t y, uint8_t *Matrix){
	uint8_t value = 1 << (y - 1);
	value = ~value;
	Matrix[x] &= value;
}
uint8_t Max7219_CheckXY(uint8_t x, uint8_t y, uint8_t *Matrix){
	uint8_t temp = 0x00 | Matrix[x];
	temp >>= (y - 1);
	uint8_t value = temp & 0x01;
	return value;
}