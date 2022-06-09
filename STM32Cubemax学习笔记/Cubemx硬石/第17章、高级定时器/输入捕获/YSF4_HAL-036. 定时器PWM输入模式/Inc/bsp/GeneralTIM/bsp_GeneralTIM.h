#ifndef __GENERAL_TIM_H__
#define __GENERAL_TIM_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
typedef struct              //测量高电平脉宽
{   
	uint8_t   ucFinishFlag;
  uint8_t   ucStartFlag;
  uint32_t  usLowPulse;
  uint32_t  usHighPulse;
	uint32_t  usCtr;
	uint32_t  usPeriod;
}STRUCT_CAPTURE;
/* 宏定义 --------------------------------------------------------------------*/
/********************通用定时器TIM参数定义，TIM2~TIM5************/
#define GENERAL_TIMx                     TIM2
#define GENERAL_TIM_RCC_CLK_ENABLE()     __HAL_RCC_TIM2_CLK_ENABLE()
#define GENERAL_TIM_RCC_CLK_DISABLE()    __HAL_RCC_TIM2_CLK_DISABLE()
#define GENERAL_TIM_IRQ                  TIM2_IRQn
#define GENERAL_TIM_IRQHANDLER           TIM2_IRQHandler

// 定义定时器预分频，定时器实际时钟频率为：84MHz/（GENERAL_TIM_PRESCALER+1）
#define GENERAL_TIM_PRESCALER           1  
// 定义定时器周期，当定时器开始计数到BASIC_TIMx_PERIOD值是更新定时器并生成对应事件和中断
#define GENERAL_TIM_PERIOD              0xFFFFFFFF  // 定时器产生中断频率为：定时器频率/0xFFFF Hz
#define GENERAL_TIM_FREQ()                (HAL_RCC_GetPCLK1Freq()<<1)

#define GENERAL_TIMX_GPIO_RCC_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE();
#define GENERAL_TIM_CH1_PORT                GPIOA
#define GENERAL_TIM_CH1_PIN                 GPIO_PIN_15
#define GENERAL_TIMx_GPIO_AF                GPIO_AF1_TIM2
#define GENERAL_TIM_CHANNEL1                TIM_CHANNEL_1
#define GENERAL_TIM_IT_CC1                  TIM_IT_CC1

#define GENERAL_TIM_CHANNEL2                TIM_CHANNEL_2
#define GENERAL_TIM_IT_CC2                  TIM_IT_CC2

#define GENERAL_TIM_STRAT_ICPolarity        TIM_INPUTCHANNELPOLARITY_FALLING         //测量的起始边沿
#define GENERAL_TIM_END_ICPolarity          TIM_INPUTCHANNELPOLARITY_RISING          //测量的结束边沿

/* 使用I/O翻转输出脉冲 */
#define GPIO_CLK_ENABLE()       __HAL_RCC_GPIOI_CLK_ENABLE()     // 输出控制脉冲给电机驱动器
#define PUL_PORT                GPIOI                            // 对应驱动器的PUL-（驱动器使用共阳接法）
#define PUL_PIN                 GPIO_PIN_5                       // 而PLU+直接接开发板的VCC


/* 扩展变量 ------------------------------------------------------------------*/
extern TIM_HandleTypeDef htimx_GeneralTIM;
/* 函数声明 ------------------------------------------------------------------*/

void GENERAL_TIMx_Init(void);

#endif	/* __GENERAL_TIM_H__ */
/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
