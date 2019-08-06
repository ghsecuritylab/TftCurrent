#include "nrf52.h"
#include "nrf_gpio.h"
#include "LCD1602.h"
#include "nrf_delay.h"

#define D7			       25
#define D6			       26
#define D5			       27
#define D4			       28
#define D3			       29
#define D2			       30
#define D1			       31
#define D0			       21

#define test			       6

#define E				       20	//�豸ʹ�� 1
#define RW			       19	//��1 / д0ѡ��
#define RS			       18	//����1 / ָ��0ѡ��

#define  DELAY1602		12
#define LCD_Port  		 {D0,D1,D2,D3,D4,D5,D6,D7}
uint16_t LCD[8]=LCD_Port;

void Pin_Init(void)
{
	nrf_gpio_cfg_output(D0);
	nrf_gpio_cfg_output(D1);
	nrf_gpio_cfg_output(D2);
	nrf_gpio_cfg_output(D3);
	nrf_gpio_cfg_output(D4);
	nrf_gpio_cfg_output(D5);
	nrf_gpio_cfg_output(D6);
	nrf_gpio_cfg_output(D7);
		
	nrf_gpio_cfg_output(RW);
	nrf_gpio_cfg_output(RS);
	nrf_gpio_cfg_output(E);
}




void LCD_Wcom(unsigned char com)
{
	int i;
	
	//nrf_gpio_pin_clear(E);	//ʧ��0
	
	//nrf_gpio_pin_clear(RS);	//ѡ��ָ��0
	nrf_gpio_pin_write(RS,0);
	
	//nrf_gpio_pin_clear(RW);	//ѡ��д0
	nrf_gpio_pin_write(RW,0);
	
	nrf_delay_us(DELAY1602);
	
	
		for(i=0;i<=7;i++)
	{
		nrf_gpio_pin_write(LCD[i],com&0x01);
		com>>=1;
	}
	

	
	nrf_delay_us(DELAY1602);
	//nrf_gpio_pin_set(E);		//ʹ��1
	nrf_gpio_pin_write(E,1);
	nrf_delay_us(DELAY1602);
	
	//nrf_gpio_pin_clear(E);	//ʧ��0
	nrf_gpio_pin_write(E,0);
	nrf_delay_us(DELAY1602);

	
}



void LCD_Wdat(unsigned char dat)
{
	int i=0;
	
	//nrf_gpio_pin_clear(E);	//ʧ��0
	
	//nrf_gpio_pin_set(RS);		//ѡ������1
	nrf_gpio_pin_write(RS,1);
	
	//nrf_gpio_pin_clear(RW);	//ѡ��д0
	nrf_gpio_pin_write(RW,0);
	nrf_delay_us(DELAY1602);
	

		for(i=0;i<=7;i++)
	{
		nrf_gpio_pin_write(LCD[i],dat&0x01);
		dat>>=1;
	}

	nrf_delay_us(DELAY1602);
	//nrf_gpio_pin_set(E);		//ʹ��1
	nrf_gpio_pin_write(E,1);
	nrf_delay_us(DELAY1602);
	
	//nrf_gpio_pin_clear(E);	//ʧ��0
	nrf_gpio_pin_write(E,0);
	nrf_delay_us(DELAY1602);
}

void LCD1602_Init(void)
{
	

	
	
	Pin_Init();						//�����������
	
	nrf_delay_us(DELAY1602);
	LCD_Wcom(0x38);				//8λ����λ��˫�С�5*7����
	nrf_delay_us(DELAY1602);
	
	LCD_Wcom(0x38);				//8λ����λ��˫�С�5*7����
	nrf_delay_us(DELAY1602);
	
	LCD_Wcom(0x38);				//8λ����λ��˫�С�5*7����
	nrf_delay_us(DELAY1602);
	
	LCD_Wcom(0x0C);				//������ʾ�����ع�꣬��겻��˸
	nrf_delay_us(DELAY1602);
	
	LCD_Wcom(0x06);				//��ʾ��ַ��������дһ�����ݺ���ʾλ������һλ
	nrf_delay_us(DELAY1602);
	
	LCD_Wcom(0x01);				//����
	nrf_delay_us(DELAY1602);
	
	LCD_Wcom(0x80);				//��ʾ����
	nrf_delay_us(DELAY1602);
}










