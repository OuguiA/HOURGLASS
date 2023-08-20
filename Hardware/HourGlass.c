#include "stm32f10x.h"    
#include "MPU6050.h"
#include <stdlib.h>
#include <stdbool.h>
#include "Max7219.h"
#include <time.h>
#include "Delay.h"
#include <stdio.h>
extern uint8_t flag_status;
enum gravity{
	down = 0,
	down_left,
	down_right,
	above,
	above_left,
	above_right,
	left,
	right
};
struct sand{
	uint8_t coordinate_x;
	uint8_t coordinate_y;
	uint8_t position;
};

struct hourglass{
	uint8_t Matrix_1[8], Matrix_2[8];
	uint8_t SANDNUM;
	struct sand *sands;
	enum gravity gravity_direction;
};

void hourglass_Init(struct hourglass *hg, int num_sands) {
			hg->SANDNUM = num_sands;
			hg->sands = (struct sand*)malloc(num_sands * sizeof(struct sand));
			for(uint8_t i = 1; i <= 8; i++){
					hg->Matrix_1[i] = 0x00;
					hg->Matrix_2[i] = 0x00;		
			}
			for(uint8_t i = 1; i <= 8; i++){
				
				for(uint8_t j = 1; j <= 8; j++){
					hg->sands[num_sands].coordinate_x = i;
					hg->sands[num_sands].coordinate_y = j;
					hg->sands[num_sands].position = 1;
					Max7219_OpenXY(i,j,hg->Matrix_1);
					num_sands --;
					if(num_sands == 0){break;}
				}
			}
			hg->gravity_direction = down_right;
}

void hourglass_set_gravity(struct hourglass *hg){
			uint8_t temp = Get_Gravity();
			switch(temp){
				case 0:hg->gravity_direction = down; 				break;
				case 1:hg->gravity_direction = down_left; 	break;
				case 2:hg->gravity_direction = down_right; 	break;
				case 3:hg->gravity_direction = above; 			break;
				case 4:hg->gravity_direction = above_left; 	break;
				case 5:hg->gravity_direction = above_right; break;
				case 6:hg->gravity_direction = left; 				break;
				case 7:hg->gravity_direction = right; 			break;
			}
}



bool if_left_null(struct hourglass *hg,struct sand *s){
	uint8_t x = s->coordinate_x;
	uint8_t y = s->coordinate_y;
	uint8_t *Matrix;
	Matrix = (s->position == 1)? hg->Matrix_1 : hg->Matrix_2;
	 switch (hg->gravity_direction) {
			case down:
					if(x == 1 || y == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_left:
					if(y == 1)
						return false;
					if(Max7219_CheckXY(x,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_right:
					if(x == 1)
								return false;
					if(Max7219_CheckXY(x - 1, y,Matrix) == 0)
								return true;
						else   return false;
					break;
					
			case right:
				if(x == 1 || y == 8)
					return false;
				if(Max7219_CheckXY(x - 1, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case left:
					if(x == 8 || y == 1)
						return false;
					if(Max7219_CheckXY(x + 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above:
					if(y == 8 || x == 8)
						return false;
					if(Max7219_CheckXY(x + 1,y + 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_left:
					if(y == 8)
						return false;
				if(Max7219_CheckXY(x, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case above_right:
				if(x == 8)
					return false;
				if(Max7219_CheckXY(x + 1, y,Matrix) == 0)
							return true;
					else   return false;
				break;
	}
}
bool if_right_null(struct hourglass *hg,struct sand *s){
	uint8_t x = s->coordinate_x;
	uint8_t y = s->coordinate_y;
	uint8_t *Matrix;
	Matrix = (s->position == 1)? hg->Matrix_1 : hg->Matrix_2;
	 switch (hg->gravity_direction) {
			case down:
					if(x == 1 || y == 8)
						return false;
					if(Max7219_CheckXY(x - 1,y + 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_left:
					if(x == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y, Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_right:
				if(y == 8)
						return false;
				if(Max7219_CheckXY(x, y + 1, Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case right:
				if(x == 8 || y == 8)
					return false;
				if(Max7219_CheckXY(x + 1, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case left:
					if(x == 1 || y == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above:
					if(y == 1 || x == 8)
						return false;
					if(Max7219_CheckXY(x + 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_left:
					if(x == 8)
						return false;
					if(Max7219_CheckXY(x + 1, y,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_right:
					if(y == 1)
							return false;
					if(Max7219_CheckXY(x, y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
	}
}

bool if_down_null(struct hourglass *hg,struct sand *s){
	uint8_t x = s->coordinate_x;
	uint8_t y = s->coordinate_y;
	uint8_t *Matrix;
	Matrix = (s->position == 1)? hg->Matrix_1 : hg->Matrix_2;
	 switch (hg->gravity_direction) {
			case down:
					if((x == 1 && y == 8) && s->position == 1 && Max7219_CheckXY(8,1,hg->Matrix_2) == 0 && flag_status == 1)
						return true;
					if(x == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_left:
					if(x == 1 || y == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y - 1, Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_right:
					if((x == 1 && y == 8) && s->position == 1 && Max7219_CheckXY(8,1,hg->Matrix_2) == 0 && flag_status == 1)
						return true;
					
					if(y == 8 || x == 1)
							return false;
					if(Max7219_CheckXY(x - 1, y + 1, Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case right:
					if((x == 1 && y == 8) && s->position == 1 && Max7219_CheckXY(8,1,hg->Matrix_2) == 0 && flag_status == 1)
						return true;
					if(y == 8)
						return false;
					if(Max7219_CheckXY(x, y + 1,Matrix) == 0)
								return true;
					else   return false;
					break;
					
			case left:
					if((x == 8 && y == 1) && s->position == 2 && Max7219_CheckXY(1,8,hg->Matrix_1) == 0 && flag_status == 1)
							return true;
					if(y == 1)
						return false;
					if(Max7219_CheckXY(x,y - 1,Matrix) == 0)
						return true;
					else   return false;
					break;
					
			case above:
				if((x == 8 && y == 1) && s->position == 2 && Max7219_CheckXY(1,8,hg->Matrix_1) == 0 && flag_status == 1)
							return true;
					if(x == 8)
						return false;
					if(Max7219_CheckXY(x + 1,y,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_left:
				if(x == 8 || y ==8)
						return false;
				if(Max7219_CheckXY(x + 1, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case above_right:
				if((x == 8 && y == 1) && s->position == 2 && Max7219_CheckXY(1,8,hg->Matrix_1) == 0 && flag_status == 1)
							return true;
				if(y == 1 || x == 8)
					 return false;
				if(Max7219_CheckXY(x + 1, y - 1,Matrix) == 0)
							return true;
				else   return false;
				break;
	}
}

void move_down(struct hourglass *hg,struct sand *s){
			 uint8_t x = s->coordinate_x;
			 uint8_t y = s->coordinate_y;
			 uint8_t *Matrix;
			 Matrix = (s->position == 1)? hg->Matrix_1 : hg->Matrix_2;
			switch (hg->gravity_direction) {
				case down:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y,Matrix);
								s->coordinate_x --;
								break;
				case down_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y - 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y --;
								break;
				case down_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y + 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y ++;
								break;
				case right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y + 1,Matrix);
								s->coordinate_y ++;
								break;
				case left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y - 1,Matrix);
								s->coordinate_y --;
								break;
				case above:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y,Matrix);
								s->coordinate_x ++;
								break;
				case above_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y + 1,Matrix);
								s->coordinate_x ++;
								s->coordinate_y ++;
								break;
				case above_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y - 1,Matrix);
								s->coordinate_x ++;
								s->coordinate_y --;
								break;
		}
}

void move_left(struct hourglass *hg,struct sand *s){
		uint8_t x = s->coordinate_x;
		uint8_t y = s->coordinate_y;
		uint8_t *Matrix;
		Matrix = (s->position == 1)? hg->Matrix_1 : hg->Matrix_2;
			switch (hg->gravity_direction) {
				case down:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y - 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y --;
								break;
				case down_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y - 1,Matrix);
								s->coordinate_y --;
								break;
				case down_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y,Matrix);
								s->coordinate_x --;
								break;
				case right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y + 1,Matrix);
								s->coordinate_y ++;
								s->coordinate_x --;
								break;
				case left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y - 1,Matrix);
								s->coordinate_y --;
								s->coordinate_x ++;
								break;
				case above:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y + 1 ,Matrix);
								s->coordinate_x ++;
								s->coordinate_y ++;
								break;
				case above_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y + 1,Matrix);
								s->coordinate_y ++;
				break;
				case above_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y,Matrix);
								s->coordinate_x ++;
				break;
		}
}

void move_right(struct hourglass *hg,struct sand *s){
		uint8_t x = s->coordinate_x;
		uint8_t y = s->coordinate_y;
		uint8_t *Matrix;
		Matrix = (s->position == 1)? hg->Matrix_1 : hg->Matrix_2;
		
			switch (hg->gravity_direction) {
				case down:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y + 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y ++;
								break;
				case down_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y,Matrix);
								s->coordinate_x --;
								break;
				case down_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x ,y + 1,Matrix);
								s->coordinate_y ++;
								break;
				case right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y + 1,Matrix);
								s->coordinate_y ++;
								s->coordinate_x ++;
								break;
				case left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y - 1,Matrix);
								s->coordinate_y --;
								s->coordinate_x --;
								break;
				case above:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y - 1 ,Matrix);
								s->coordinate_x ++;
								s->coordinate_y --;
								break;
				case above_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y,Matrix);
								s->coordinate_x ++;
				break;
				case above_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y - 1,Matrix);
								s->coordinate_y --;
				break;
				
		}
}

void sand_next(struct hourglass *hg,struct sand *s){
	bool down_ifNull = if_down_null(hg,s);
	if(down_ifNull == true){
		 if((s->coordinate_x == 1 && s->coordinate_y == 8) && s->position == 1 
			 && ((hg->gravity_direction == down_right)||(hg->gravity_direction == down)||(hg->gravity_direction == right))){
					Max7219_CloseXY(1,8,hg->Matrix_1);
					Max7219_OpenXY(8,1,hg->Matrix_2);
					s->coordinate_x = 8;
					s->coordinate_y = 1;
					s->position = 2;
					flag_status = 0;
					TIM_Cmd(TIM2, ENABLE);
			}
			else if((s->coordinate_x == 8 && s->coordinate_y == 1) && s ->position == 2 
				&& ((hg->gravity_direction == above_right)||(hg->gravity_direction == above)||(hg->gravity_direction == left))){
					Max7219_CloseXY(8,1,hg->Matrix_2);
					Max7219_OpenXY(1,8,hg->Matrix_1);
					s->coordinate_x = 1;
					s->coordinate_y = 8;
					s->position = 1;
					flag_status = 0;
					TIM_Cmd(TIM2, ENABLE);
			}
			else move_down(hg,s);
	}
	else{
		bool left_ifNull = if_left_null(hg,s);
		bool right_ifNull = if_right_null(hg,s);
				if(left_ifNull == true && right_ifNull == true){
						uint8_t index = rand() %2;
						if(index == 0)
								move_left(hg,s);
						else
								move_right(hg,s);
				}
				else if(left_ifNull == true && right_ifNull == false)
						move_left(hg,s);   
			
				else if(left_ifNull == false && right_ifNull == true)
						move_right(hg,s);
		}
}

