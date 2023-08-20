#include "stm32f10x.h"   // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "MPU6050.h"
#include "MPU6050Reg.h"
#include "Max7219.h"
#include "HourGlass.h"
#include <stdbool.h>

struct hourglass hg;
uint8_t flag_status = 1;
int main(){
		Timer_Init();
		OLED_Init();
		Max7219_Init(); 
		MPU6050_Init();
		uint8_t num_sands = 60; 
		hourglass_Init(&hg, num_sands);
		OLED_ShowString(4,1,"gravity :");
	
		while(1){
			OLED_ShowNum(4,11,hg.gravity_direction,2);
			hourglass_set_gravity(&hg);
			for(uint8_t i = 1; i <= num_sands; i ++){
				sand_next(&hg,&hg.sands[i]);
			}
			Max7219_1_Scan(hg.Matrix_1);
			Max7219_2_Scan(hg.Matrix_2);
			Delay_ms(60);
		}	
}


