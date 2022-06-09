#ifndef __ADVANCED_TIM_H__
#define __ADVANCED_TIM_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/

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

// ���嶨ʱ��Ԥ��Ƶ����ʱ��ʵ��ʱ��Ƶ��Ϊ��168MHz/��ADVANCED_TIMx_PRESCALER+1��
#define ADVANCED_TIM_PRESCALER            167  // ʵ��ʱ��Ƶ��Ϊ��1MHz

// ���嶨ʱ�����ڣ�����ʱ����ʼ������ADVANCED_TIMx_PERIODֵ�����ظ������Ĵ���Ϊ0ʱ���¶�ʱ�������ɶ�Ӧ�¼����ж�
#define ADVANCED_TIM_PERIOD               32767  // ��ʱ�������ж�Ƶ��Ϊ��1MHz/(32768)��30Hz���������Ƶ�ʡ�30Hz
// ����߼���ʱ���ظ������Ĵ���ֵ��
#define ADVANCED_TIM_REPETITIONCOUNTER    0

/* ��չ���� ------------------------------------------------------------------*/
extern TIM_HandleTypeDef htimx;
/* �������� ------------------------------------------------------------------*/

void ADVANCED_TIMx_Init(void);

#endif	/* __ADVANCED_TIM_H__ */
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
