#ifndef _XYSHOW_H
#define _XYSHOW_H
#include "sys.h"


#define xy_num	3300

extern DAC_HandleTypeDef DAC1_Handler;//DAC¾ä±ú

typedef struct
{
		u16 x;
		u16 y;
}position_t;

typedef struct
{
	position_t start;
	position_t end;
}line_t;
typedef enum
{
	sheng = 0,
	ri,
	kuai,
	le,
	test
}chars_t;
void setvolity(u16 vol_x, u16 vol_y);
void showline(position_t start,position_t end);
void chars_init(void);
void display_char(chars_t chars);


#endif
