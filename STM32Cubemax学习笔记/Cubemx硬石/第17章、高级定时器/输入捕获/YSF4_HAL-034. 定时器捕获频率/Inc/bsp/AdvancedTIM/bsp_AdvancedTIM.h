#ifndef __ADVANCED_TIM_H__
#define __ADVANCED_TIM_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/

#define ADVANCED_TIMx                       TIM1
#define ADVANCED_TIMx_GPIO_AF               GPIO_AF1_TIM1
#define ADVANCED_TIM_RCC_CLK_ENABLE()       __HAL_RCC_TIM1_CLK_ENABLE()
#define ADVANCED_TIM_RCC_CLK_DISABLE()      __HAL_RCC_TIM1_CLK_DISABLE()
#define ADVANCED_TIM_GPIO_RCC_CLK_ENABLE()  {__HAL_RCC_GPIOA_CLK_ENABLE();__HAL_RCC_GPIOB_CLK_ENABLE();}
#define ADVANCED_TIM_CH1_PORT               GPIOA
#define ADVANCED_TIM_CH1_PIN                GPIO_PIN_8

//#define ADVANCED_TIMx                       TIM8
//#define ADVANCED_TIMx_GPIO_AF               GPIO_AF3_TIM8
//#define ADVANCED_TIM_RCC_CLK_ENABLE()       __HAL_RCC_TIM8_CLK_ENABLE()
//#define ADVANCED_TIM_RCC_CLK_DISABLE()      __HAL_RCC_TIM8_CLK_DISABLE()
//#define ADVANCED_TIM_GPIO_RCC_CLK_ENABLE()  {__HAL_RCC_GPIOI_CLK_ENABLE();__HAL_RCC_GPIOH_CLK_ENABLE();}
//#define ADVANCED_TIM_CH1_PORT               GPIOI
//#define ADVANCED_TIM_CH1_PIN                GPIO_PIN_5
//#define ADVANCED_TIM_CH2_PORT               GPIOI
//#define ADVANCED_TIM_CH2_PIN                GPIO_PIN_6
//#define ADVANCED_TIM_CH3_PORT               GPIOI
//#define ADVANCED_TIM_CH3_PIN                GPIO_PIN_7
//#define ADVANCED_TIM_CH4_PORT               GPIOI
//#define ADVANCED_TIM_CH4_PIN                GPIO_PIN_2
//
//#define ADVANCED_TIM_CH1N_PORT              GPIOH
//#define ADVANCED_TIM_CH1N_PIN               GPIO_PIN_13
//#define ADVANCED_TIM_CH2N_PORT              GPIOH
//#define ADVANCED_TIM_CH2N_PIN               GPIO_PIN_14
//#define ADVANCED_TIM_CH3N_PORT              GPIOH
//#define ADVANCED_TIM_CH3N_PIN               GPIO_PIN_15
//
//#define ADVANCED_TIM_BKIN_PORT              GPIOI
//#define ADVANCED_TIM_BKIN_PIN               GPIO_PIN_4

// 定义定时器预分频，定时器实际时钟频率为：168MHz/（ADVANCED_TIMx_PRESCALER+1）
#define ADVANCED_TIM_PRESCALER            167  // 实际时钟频率为：1MHz

// 定义定时器周期，当定时器开始计数到ADVANCED_TIMx_PERIOD值并且重复计数寄存器为0时更新定时器并生成对应事件和中断
#define ADVANCED_TIM_PERIOD               32767  // 定时器产生中断频率为：1MHz/(32768)≈30Hz，输出脉冲频率≈30Hz
// 定义高级定时器重复计数寄存器值，
#define ADVANCED_TIM_REPETITIONCOUNTER    0

/* 扩展变量 ------------------------------------------------------------------*/
extern TIM_HandleTypeDef htimx;
/* 函数声明 ------------------------------------------------------------------*/

void ADVANCED_TIMx_Init(void);

#endif	/* __ADVANCED_TIM_H__ */
/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
