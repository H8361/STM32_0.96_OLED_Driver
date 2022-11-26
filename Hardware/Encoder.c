#include "stm32f10x.h"                  // Device header

uint32_t Encoder_Count = 0 ;
int32_t Encoder_SignedCount = 0;

/**
* @brief 初始化 Encoder
* @param 无
* @retval 无
*
*/
void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; // 中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; // 上升沿触发
	
	EXTI_Init(&EXTI_InitStructure);
	
	// 配置NVIC的合理优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

}


/**
* @brief 获取无符号的计数值
* @param
* @retval 
*
*/
uint32_t Encoder_GetCount(void)
{
	uint32_t tmp = Encoder_Count;
	Encoder_Count = 0;
	return tmp;
}

/**
* @brief 获取右符号的计数值
* @param
* @retval 
*
*/
int32_t Encoder_GetSignedCount(void)
{
	int32_t tmp = Encoder_SignedCount;
	Encoder_SignedCount = 0;
	return tmp;
}

/**
* @brief 逆时针旋转中断函数
* @param
* @retval 
*
*/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){
			// 反转
			Encoder_Count--;
			Encoder_SignedCount--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/**
* @brief 顺时针旋转中断函数
* @param
* @retval 
*
*/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0){
			// 正转
			Encoder_Count++;
			Encoder_SignedCount++;
		}
	
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}



