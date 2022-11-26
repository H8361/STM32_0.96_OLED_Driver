#ifndef __ENCODER_H__
#define __ENCODER_H__
extern uint32_t Encoder_Count;
extern int32_t Encoder_SignedCount;

void Encoder_Init(void);
uint32_t Encoder_GetCount(void);
int32_t Encoder_GetSignedCount(void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
#endif
