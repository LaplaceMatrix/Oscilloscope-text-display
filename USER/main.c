#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "usmart.h"
#include "adc.h"
#include "dac.h"
#include "XYShow.h"
/************************************************
 ALIENTEK 阿波罗STM32F7开发板 实验22
 DAC实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

int main(void)
{
	
 	u16 t=0;	 
	u16 dacval=0;
	u8 key;	
	float temp;
    Cache_Enable();                 //打开L1-Cache
    HAL_Init();				        //初始化HAL库
    Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
    delay_init(216);                //延时初始化
	uart_init(115200);		        //串口初始化
    usmart_dev.init(108); 		    //初始化USMART	
    LED_Init();                     //初始化LED
    KEY_Init();                     //初始化按键
    SDRAM_Init();                   //初始化SDRAM
    LCD_Init();                     //LCD初始化
    MY_ADC_Init();                  //初始化ADC1
    DAC1_Init();                    //初始化DAC1
    
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Apollo STM32F4/F7");	
	LCD_ShowString(30,70,200,16,16,"DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2016/7/12");	 
	LCD_ShowString(30,130,200,16,16,"WK_UP:+  KEY1:-");	 
	POINT_COLOR=BLUE;//设置字体为蓝色      	 
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V"); 	
    
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);//初始值为0 

	chars_init();

    while(1)
	{
		t++;
		key=KEY_Scan(0);
		if(t%100 == 0)LED0_Toggle;

		
		if(key==WKUP_PRES)dacval++;
		else if(key==2)dacval++;
		if(dacval%4 == 0)display_char(sheng);
		else if(dacval%4 == 1)display_char(ri);
		else if(dacval%4 == 2)display_char(kuai);
		else if(dacval%4 == 3)display_char(le);
		//delay_ms(10);	
	}
}
