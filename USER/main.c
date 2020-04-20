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
 ALIENTEK ������STM32F7������ ʵ��22
 DACʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

int main(void)
{
	
 	u16 t=0;	 
	u16 dacval=0;
	u8 key;	
	float temp;
    Cache_Enable();                 //��L1-Cache
    HAL_Init();				        //��ʼ��HAL��
    Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
    delay_init(216);                //��ʱ��ʼ��
	uart_init(115200);		        //���ڳ�ʼ��
    usmart_dev.init(108); 		    //��ʼ��USMART	
    LED_Init();                     //��ʼ��LED
    KEY_Init();                     //��ʼ������
    SDRAM_Init();                   //��ʼ��SDRAM
    LCD_Init();                     //LCD��ʼ��
    MY_ADC_Init();                  //��ʼ��ADC1
    DAC1_Init();                    //��ʼ��DAC1
    
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Apollo STM32F4/F7");	
	LCD_ShowString(30,70,200,16,16,"DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2016/7/12");	 
	LCD_ShowString(30,130,200,16,16,"WK_UP:+  KEY1:-");	 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ      	 
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V"); 	
    
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);//��ʼֵΪ0 

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
