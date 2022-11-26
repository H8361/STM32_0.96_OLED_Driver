#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

#include "stm32f10x.h"

#define OLED_ADDRESS	0x78 // 通过调整OR电阻，屏可以 0x78和0x7A两个地址，默认0x78
uint32_t OLED_Pow(uint32_t X, uint32_t Y);
void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);

void OLED_ShowChar(uint8_t x, uint8_t y, char Char,unsigned char TextSize);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_ShowNum(unsigned char x, unsigned char y, uint32_t Num,uint8_t Length, unsigned char TextSize);
void OLED_ShowSignedNum(unsigned char x, unsigned char y, int32_t Num,uint8_t Length, unsigned char TextSize);
void OLED_ShowHexNum(uint8_t x, uint8_t y, uint32_t Num,uint8_t Length,unsigned char TextSize);
void OLED_ShowBinNum(uint8_t x, uint8_t y, uint32_t Num,uint8_t Length,unsigned char TextSize);

#endif
