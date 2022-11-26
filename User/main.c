#include "stm32f10x.h"
#include "OLED_I2C.h"
#include "Delay.h"
//#include "Test_char.h"  // 测试 OLED_ShowChar()
//#include "Usart1.h"     // 串口调试


uint8_t i; 
uint32_t Num = 0;
int32_t SignedNum = 0 ;
int main(void)
{
	// {(x,y) | x∈[0,127] , y∈[0,7]}

	extern const unsigned char BMP1[];
//	extern const unsigned char BMP2[];
//	extern const unsigned char BMP3[];
	
	DelayInit();
	I2C_Configuration();
	OLED_Init();

	
	OLED_Fill(0xFF);//全屏点亮
	DelayMs(200);
	OLED_Fill(0x00);//全屏灭
	DelayMs(200);
	
	
	// 串口通信，进行输出调试
//	USART1_Init();

//	uint8_t MyArray[] = {0x41,0x42,0x43,0x44};
//	USART1_SendArray(MyArray,4);
//	USART1_SendString("\r\nHello World!\r\n");
//	USART1_SendNumber(12345,5);
//	
//	printf("\r\nNumber: %d\r\n",888);
//	
//	char String[100];
//	sprintf(String,"\r\nNumber: %d\r\n",999); // 先将字符串重定向到缓冲区，直接输出缓冲区的内容
//	USART1_SendString(String);
//	USART1_Printf("Number:%d\r\n",777);
//	
//	USART1_Printf("你好，世界");
	

//	Char_test_font_1(); // 测试 1 号字体
//	Char_test_font_2(); // 测试 2 号字体

	
//	显示无符号的整数
	OLED_ShowStr(30,0,(unsigned char *)"Unsigned Num",1);
	OLED_ShowNum(0,2,99,3,1); // y 为偶数，剩余像素宽度满足字符显示长度
	OLED_ShowNum(123,2,99,3,1);// y 为偶数，剩余像素宽度不满足字符显示长度（不足6个像素）
	OLED_ShowNum(0,6,99,6,1); // y 为奇数，剩余像素宽度满足字符显示长度
	OLED_ShowNum(122,6,99,6,1);// y 为7奇数，越界，会进行换行（换到首行）
	DelayS(2);
	OLED_CLS();


//	有符号整数
	OLED_ShowStr(30,0,(unsigned char *)"Signed Num",1);
	OLED_ShowSignedNum(0,2,-99,4,1); // 字体大小 1
	OLED_ShowSignedNum(123,2,-99,4,1);

	OLED_ShowSignedNum(0,6,-99,4,2); // 字体大小 2
	OLED_ShowSignedNum(122,6,-99,4,2);
	
	DelayS(1);
	OLED_CLS(); // 清屏

//	16进制数
	
	OLED_ShowStr(30,0,(unsigned char *)"Hex Num",1);
	OLED_ShowHexNum(0,2,0xAB,4,1);
	OLED_ShowHexNum(123,2,0xAB,4,1);
	
	OLED_ShowHexNum(0,6,0xAB,4,2);
	OLED_ShowHexNum(121,6,0xAB,4,2);
	
	DelayS(1);
	OLED_CLS(); // 清屏
	
//	2进制数
	OLED_ShowStr(30,0,(unsigned char *)"Bin Num",1);
	OLED_ShowBinNum(0,0,0xAB,8,1);
	OLED_ShowBinNum(123,0,0xAB,8,1);
	
	OLED_ShowBinNum(0,2,0xAB,8,2);
	OLED_ShowBinNum(121,2,0xAB,8,2);
	
	DelayS(1);
	OLED_CLS(); // 清屏

//	字符
	OLED_ShowStr(30,0,(unsigned char *)"Char",1);
	OLED_ShowChar(0,0,'A',1);
	OLED_ShowChar(124,0,'A',1);
	
	OLED_ShowChar(0,2,'A',2);
	OLED_ShowChar(121,2,'A',2);
	
	DelayS(1);
	OLED_CLS(); // 清屏

//	字符串
	OLED_ShowStr(0,0,(unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",1);
	OLED_ShowStr(123,0,(unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",1);// 会出现覆盖情况
	
	OLED_ShowStr(0,2,(unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",2);
	OLED_ShowStr(121,2,(unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",2); // 超出的部分会被丢弃
	//OLED_ShowStr(0,6,(unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",2); // 超出的部分会被丢弃
	DelayS(1);
	OLED_CLS(); // 清屏
	OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//测试BMP位图显示

//	中文显示
	uint8_t i;
	for(i=0;i<5;i++)
	{
		OLED_ShowCN(22+i*16,0,i);//测试显示中文
	}

	
//	图像显示
	OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//测试BMP位图显示
	DelayS(1);
	OLED_CLS();

	
//	uint8_t RxData; // 串口调试使用
	while(1)
	{
		
		// 串口收发数据
		// 查询方式 收到数据,在OLED显示屏上显示
//		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET){
//			RXData = USART_ReceiveData(USART1);
//			OLED_ShowHexNum(0,0,RXData,2,2);
//		}
		// 中断方式，收到数据在 OLED 显示屏上显示
//		if(USART1_GetRxFlag() == 1){
//			RxData = USART1_GetRxData();
//			USART1_SendByte(RxData);
//			OLED_ShowHexNum(0,0,RxData,2,2);
//		}
		
	}
}
