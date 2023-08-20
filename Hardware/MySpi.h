#ifndef __MYSPI_H
#define __MYSPI_H

void SPI_W_SS(uint8_t BitValue);
void SPI_W_SCK(uint8_t BitValue);
void SPI_W_MOSI(uint8_t BitValue);
uint8_t SPI_R_MISO();
void MySpi_Init();
void SPI_Start();
void SPI_Stop();
uint8_t SPI_SwapByte(uint8_t byte);

#endif