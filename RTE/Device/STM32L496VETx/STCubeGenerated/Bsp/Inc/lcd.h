#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000

#define LCD_Width 	240
#define LCD_Height 	240

#define	LCD_PWR(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET))
#define	LCD_RST(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET))
#define	LCD_DC(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET))
#define	LCD_CS(n)		(n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET))

void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Write_HalfWord(const uint16_t da);
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Clear(uint16_t color);
//void LCD_Fill(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);
//void LCD_Fill_Buf(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t* clr_buf);
//void LCD_Draw_Point(uint16_t x, uint16_t y);
//void LCD_Draw_ColorPoint(uint16_t x, uint16_t y,uint16_t color);
//void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
//void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
//void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r);
//void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint8_t size);
//void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);
//void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
//void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,char *p);
//void LCD_Show_Image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p);

int32_t Disp0_DrawBitmap(int16_t x, 
                        int16_t y, 
                        int16_t width, 
                        int16_t height, 
                        const uint8_t *bitmap);

#endif
