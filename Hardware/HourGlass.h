#ifndef __HOURGLASS_H
#define __HOURGLASS_H
#include <stdbool.h>
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
struct sand {
	uint8_t coordinate_x;
	uint8_t coordinate_y;
	uint8_t position;
};

struct hourglass {
	uint8_t Matrix_1[8], Matrix_2[8];
	uint8_t SANDNUM;
	struct sand *sands;
	enum gravity gravity_direction;
};

void hourglass_Init(struct hourglass *hg, int num_sands);
bool if_left_null(struct hourglass *hg,struct sand *s);
bool if_right_null(struct hourglass *hg,struct sand *s);
bool if_dow_null(struct hourglass *hg,struct sand *s);

void move_down(struct hourglass *hg,struct sand *s);
void move_left(struct hourglass *hg,struct sand *s);
void move_right(struct hourglass *hg,struct sand *s);
void hourglass_set_gravity(struct hourglass *hg);
void sand_next(struct hourglass *hg,struct sand *s);

#endif
