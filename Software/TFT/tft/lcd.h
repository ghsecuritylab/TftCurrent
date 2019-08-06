/*
 * lcd.h
 *
 *  Created on: 2019-7-4
 *      Author: Jason
 */

#ifndef LCD_H_
#define LCD_H_

typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;


////IO����
//sbit LCD_CS     =P0^0;     //Ƭѡ
//sbit LCD_DC     =P0^2;	  //����/�����л�
//sbit LCD_SDI    =P1^5;	  //����
//sbit LCD_SCK    =P1^7;	  //ʱ��
//sbit LCD_REST   =P0^1;	  //��λ

//#define LCD_SDI 20
//#define LCD_SCK 30
//#define LCD_SDO 19
////#define LCD_CS 21
////#define LCD_CS 2
//#define LCD_CS_REAL 21
//
//#define LCD_REST 29
//#define LCD_DC 31



#define LCD_SDI 31
#define LCD_SCK 27
#define LCD_SDO 2
#define LCD_CS 25
//#define LCD_CS 16
#define LCD_CS_REAL 25

#define LCD_REST 4
#define LCD_DC 26



#include "nrf_delay.h"
#define delay_ms nrf_delay_ms


/*************** high performer GPIO operation ****************/

/**
 * high performer GPIO operation - faster
 *
 * different:
 * 	clear/set:0.88us/0.13us
 * 	toggle: 1.30us/0.31us
 *
 * 	52832:
 * 	clear/set:	17ns
 * 	toggle: 	60ns
 */
#define GPIO_TOGGLE(PIN)	((NRF_GPIO->OUT) ^= (1 << (PIN)))
#define GPIO_HIGH(PIN)	((NRF_GPIO->OUTSET) = (1 << (PIN)))
#define GPIO_LOW(PIN)	((NRF_GPIO->OUTCLR) = (1 << (PIN)))
#define GPIO_READ(PIN)	((NRF_GPIO->IN >> PIN) & 0x01)


/*************** high performer GPIO operation ****************/





//SPI��ʾ���ӿ�
//LCD_RST
#define SPILCD_RST_HIGH  GPIO_HIGH(LCD_REST)
#define SPILCD_RST_LOW GPIO_LOW(LCD_REST)
//LCD_RS//dc
#define SPILCD_RS_HIGH  GPIO_HIGH(LCD_DC)
#define SPILCD_RS_LOW  GPIO_LOW(LCD_DC)
//LCD_CS
//#define SPILCD_CS_HIGH GPIO_HIGH(LCD_CS)
//#define SPILCD_CS_LOW  GPIO_LOW(LCD_CS)
#define SPILCD_CS_HIGH
#define SPILCD_CS_LOW






//LCD��Ҫ������
typedef struct {
	u16 width; //LCD ���
	u16 height; //LCD �߶�
	u16 id; //LCD ID
	u8 wramcmd; //��ʼдgramָ��
	u8 setxcmd; //����x����ָ��
	u8 setycmd; //����y����ָ��
} _lcd_dev;

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ


//LCD��ַ�ṹ��
typedef struct {
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ��������������
//ע������ʱSTM32�ڲ�������һλ����! 111110=0X3E
#define LCD_BASE        ((u32)(0x60000000 | 0x0007FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

void LCD_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u16 Color);	 												//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//���ù��
void LCD_DrawPoint(u16 x,u16 y);											//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//���ٻ���
void Draw_Circle(u16 x0,u16 y0,u8 r);										//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//��ʾһ���ַ���,12/16����

void showimage(u16 x,u16 y); //��ʾ40*40ͼƬ
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void LCD_WR_DATA8(u8 da);   //д8λ����

void showhanzi16(unsigned int x,unsigned int y,unsigned char index);//16*16����
void showhanzi32(unsigned int x,unsigned int y,unsigned char index);//32*32����

















#endif /* LCD_H_ */
