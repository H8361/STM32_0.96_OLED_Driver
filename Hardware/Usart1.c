#include "USART1.h"

uint8_t G_RXData,G_RXFlag;


void  USART1_Init()
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 设置 GPIO 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // USART1 的输出引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // USART1 的输入引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	// 设置 USART
	USART_DeInit(USART1);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // 同时开启发送和接收
	
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	// 使用查询或者中断的方式可以完成初始化
	// 中断需要开启的代码（以下部分代码）
	// 开启中断(还需要添加中断处理函数)
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel  = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}

void USART1_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void USART1_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0;i<Length;i++)
	{
		USART1_SendByte(Array[i]);
	}
}

void USART1_SendString(char *String)
{
	uint8_t i;
	for(i = 0; String[i]!='\0';i++){
		USART1_SendByte(String[i]);
	}
	
}

uint32_t Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	while(Y--){
		Result *= X;
	}
	return Result;
}

void USART1_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i = 0;i<Length;i++){
		USART1_SendByte(Number / Pow(10,Length - i - 1) % 10 + '0'); // '0' 对应于 0x30
	}
}

// 移植printf （printf 底层调用的是  fputc ）
// 串口1 独占  printf 
// 其他串口不可在使用，所以可以直接使用 sprintf()，其他串口仍然可以使用
int fputc(int ch,FILE *filp)
{
	USART1_SendByte(ch);
	return ch;
}

void USART1_Printf(char *fmt,...)
{
	char String[100];
	va_list arg;
	va_start(arg,fmt);
	vsprintf(String,fmt,arg);
	va_end(arg);
	USART1_SendString(String);
}


void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)
	{
		G_RXData = USART_ReceiveData(USART1);
		G_RXFlag  = 1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}

}

uint8_t USART1_GetRxFlag(void)
{
	if(G_RXFlag){
		G_RXFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t USART1_GetRxData(void)
{
	return G_RXData;
}