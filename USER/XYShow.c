#include "XYShow.h"
#include "delay.h"

//vol:0~3300,代表0~3.3V
void setvolity(u16 vol_x, u16 vol_y)
{
	double temp;
	temp=vol_x/1000.0;
	temp=temp*4096/3.3;
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,temp);//12位右对齐数据格式设置DAC值
	
	temp=vol_y/1000.0;
	temp=temp*4096/3.3;
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,temp);//12位右对齐数据格式设置DAC值
}
//坐标为0到3300，与vol设置一致
u16 min(u16 a, u16 b)
{
	if(a>b)return b;
	else return a;
}
double error_x, error_y;
u16		min_x, min_y;
void showline(position_t start,position_t end)
{
	u16 i;
	//计算差值
	error_x = end.x - start.x;
	error_y = end.y - start.y;
	//if(error_x<0)error_x = -error_x;
	//if(error_y<0)error_y = -error_y;
	//计算平均差值
	error_x = error_x / xy_num *1.0;
	error_y = error_y / xy_num *1.0;
	
	//计算最小值
	//min_x = min(end.x,start.x);
	//min_y = min(end.y,start.y);
	//插值运算
	for(i = 0; i < xy_num; i++)
		setvolity(start.x + error_x * i, start.y + error_y * i);
	//delay_ms(1);
}
line_t sheng_lines[5];
line_t ri_lines[5];
line_t kuai_lines[9];
line_t le_lines[7];
line_t test_line;
void chars_init(void)
{
	//生
	sheng_lines[0].start.x = 500;	sheng_lines[0].start.y = 2000;	sheng_lines[0].end.x = 1000;	sheng_lines[0].end.y = 3000;
	sheng_lines[1].start.x = 750;	sheng_lines[1].start.y = 2500;	sheng_lines[1].end.x = 2500;	sheng_lines[1].end.y = 2500;
	sheng_lines[2].start.x = 1500;sheng_lines[2].start.y = 3000;	sheng_lines[2].end.x = 1500;	sheng_lines[2].end.y = 0;
	sheng_lines[3].start.x = 750;	sheng_lines[3].start.y = 1500;	sheng_lines[3].end.x = 2250;	sheng_lines[3].end.y = 1500;
	sheng_lines[4].start.x = 500;	sheng_lines[4].start.y = 0;	    sheng_lines[4].end.x = 2500;	sheng_lines[4].end.y = 0;
	
	//日
	ri_lines[0].start.x = 500;	ri_lines[0].start.y = 3000;	ri_lines[0].end.x = 500;	ri_lines[0].end.y = 0;
	ri_lines[1].start.x = 500;	ri_lines[1].start.y = 3000;	ri_lines[1].end.x = 2500;	ri_lines[1].end.y = 3000;
	ri_lines[2].start.x = 2500;	ri_lines[2].start.y = 3000;	ri_lines[2].end.x = 2500;	ri_lines[2].end.y = 0;
	ri_lines[3].start.x = 500;	ri_lines[3].start.y = 0;	  ri_lines[3].end.x = 2500;	ri_lines[3].end.y = 0;
	ri_lines[4].start.x = 500;	ri_lines[4].start.y = 1500;	ri_lines[4].end.x = 2500;	ri_lines[4].end.y = 1500;
	
	//快
	kuai_lines[0].start.x = 750;	kuai_lines[0].start.y = 1750;	kuai_lines[0].end.x = 500;	kuai_lines[0].end.y = 1000;
	kuai_lines[1].start.x = 750;	kuai_lines[1].start.y = 1750;	kuai_lines[1].end.x = 1000;	kuai_lines[1].end.y = 1500;
	kuai_lines[2].start.x = 750;	kuai_lines[2].start.y = 3000;	kuai_lines[2].end.x = 750;	kuai_lines[2].end.y = 0;
	kuai_lines[3].start.x = 1000;	kuai_lines[3].start.y = 2000;	kuai_lines[3].end.x = 2250;	kuai_lines[3].end.y = 2000;
	kuai_lines[4].start.x = 2250;	kuai_lines[4].start.y = 2000;	kuai_lines[4].end.x = 2250;	kuai_lines[4].end.y = 1000;
	kuai_lines[5].start.x = 800;	kuai_lines[5].start.y = 1000;	kuai_lines[5].end.x = 2500;	kuai_lines[5].end.y = 1000;
	kuai_lines[6].start.x = 1500;	kuai_lines[6].start.y = 3000;	kuai_lines[6].end.x = 1500;	kuai_lines[6].end.y = 1000;
	kuai_lines[7].start.x = 1500;	kuai_lines[7].start.y = 1000;	kuai_lines[7].end.x = 800;	kuai_lines[7].end.y = 0;
	kuai_lines[8].start.x = 1750;	kuai_lines[8].start.y = 1000;	kuai_lines[8].end.x = 2250;	kuai_lines[8].end.y = 0;
	
	//乐
	le_lines[0].start.x = 2250;	le_lines[0].start.y = 2750;	le_lines[0].end.x = 750;	le_lines[0].end.y = 2500;
	le_lines[1].start.x = 750;	le_lines[1].start.y = 2500;	le_lines[1].end.x = 750;	le_lines[1].end.y = 1500;
	le_lines[2].start.x = 750;	le_lines[2].start.y = 1500;	le_lines[2].end.x = 2250;	le_lines[2].end.y = 1500;
	le_lines[3].start.x = 1500;	le_lines[3].start.y = 2500;	le_lines[3].end.x = 1500;	le_lines[3].end.y = 0;
	le_lines[4].start.x = 1500;	le_lines[4].start.y = 0;	  le_lines[4].end.x = 1250;	le_lines[4].end.y = 250;
	le_lines[5].start.x = 1250;	le_lines[5].start.y = 1000;	le_lines[5].end.x = 750;	le_lines[5].end.y = 500;
	le_lines[6].start.x = 1750;	le_lines[6].start.y = 1000;	le_lines[6].end.x = 2250;	le_lines[6].end.y = 500;
	
	//测试线
	test_line.start.x = 0;	test_line.start.y = 0;	test_line.start.x = 3300;	test_line.start.y = 3300;
}
void display_char(chars_t chars)
{
	if(chars == sheng)
	{
		showline(sheng_lines[0].start,sheng_lines[0].end);
		showline(sheng_lines[1].start,sheng_lines[1].end);
		showline(sheng_lines[2].start,sheng_lines[2].end);
		showline(sheng_lines[3].start,sheng_lines[3].end);
		showline(sheng_lines[4].start,sheng_lines[4].end);
	}
	else if(chars == ri)
	{
		showline(ri_lines[0].start,ri_lines[0].end);
		showline(ri_lines[1].start,ri_lines[1].end);
		showline(ri_lines[2].start,ri_lines[2].end);
		showline(ri_lines[3].start,ri_lines[3].end);
		showline(ri_lines[4].start,ri_lines[4].end);
	}
	else if(chars == kuai)
	{
		showline(kuai_lines[0].start,kuai_lines[0].end);
		showline(kuai_lines[1].start,kuai_lines[1].end);
		showline(kuai_lines[2].start,kuai_lines[2].end);
		showline(kuai_lines[3].start,kuai_lines[3].end);
		showline(kuai_lines[4].start,kuai_lines[4].end);
		showline(kuai_lines[5].start,kuai_lines[5].end);
		showline(kuai_lines[6].start,kuai_lines[6].end);
		showline(kuai_lines[7].start,kuai_lines[7].end);
		showline(kuai_lines[8].start,kuai_lines[8].end);
	}
	else if(chars == le)
	{
		showline(le_lines[0].start,le_lines[0].end);
		showline(le_lines[1].start,le_lines[1].end);
		showline(le_lines[2].start,le_lines[2].end);
		showline(le_lines[3].start,le_lines[3].end);
		showline(le_lines[4].start,le_lines[4].end);
		showline(le_lines[5].start,le_lines[5].end);
		showline(le_lines[6].start,le_lines[6].end);
	}
	else showline(test_line.start,test_line.end);
}






