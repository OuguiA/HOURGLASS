#include "stm32f10x.h"                  // Device header

 
void SPI_W_SS(uint8_t BitValue){
	GPIO_WriteBit(GPIOA, GPIO_Pin_4,(BitAction)BitValue);
}
void SPI_W_SCK(uint8_t BitValue){
	GPIO_WriteBit(GPIOA, GPIO_Pin_5,(BitAction)BitValue);
}
void SPI_W_MOSI(uint8_t BitValue){
	GPIO_WriteBit(GPIOA, GPIO_Pin_7,(BitAction)BitValue);
}
uint8_t SPI_R_MISO(){
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySpi_Init(){
		GPIO_InitTypeDef GPIO_InitStruct;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		SPI_W_SS(1);
		SPI_W_SCK(0);
}

void SPI_Start(){
	SPI_W_SS(0);
}
void SPI_Stop(){
	SPI_W_SS(1);
}

uint8_t SPI_SwapByte(uint8_t byte){
	uint8_t ReceiveByte = 0x00;
	uint8_t i;
	for(i = 0; i < 8; i++){
		SPI_W_MOSI(byte & (0x80 >> i));
		SPI_W_SCK(1);
		if(SPI_R_MISO() == 1){ReceiveByte |= (0x80 >> i);}
		SPI_W_SCK(0);
	}
	return ReceiveByte;
}
