/**
  ******************************************************************************
  * 文件名程: bsp_BasicTIM.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2017-03-30
  * 功    能: 基本定时器TIM6 & TIM7底层驱动程序
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F4Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
#include "GeneralTIM/bsp_GeneralTIM.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
TIM_HandleTypeDef htimx_GeneralTIM;
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 定时器通道1引脚初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base == &htimx_GeneralTIM)
  {
    /* 基本定时器外设时钟使能 */
    GENERAL_TIM_RCC_CLK_ENABLE();
    GENERAL_TIMX_GPIO_RCC_CLK_ENABLE();
    GPIO_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = GENERAL_TIM_CH1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;     // 输入模式
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GENERAL_TIMx_GPIO_AF;
    HAL_GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStruct);
    
    /* 脉冲输出引脚配置 */   
    GPIO_InitStruct.Pin = PUL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = 0;        // GPIO引脚用做TIM复用功能
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(PUL_PORT, &GPIO_InitStruct);
      
    /* 配置定时器中断优先级并使能 */
    HAL_NVIC_SetPriority(GENERAL_TIM_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(GENERAL_TIM_IRQ);
  }
}
/**
  * 函数功能: 基本定时器初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void GENERAL_TIMx_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_SlaveConfigTypeDef sslaveConfig;
  TIM_IC_InitTypeDef sConfigIC;
  
  GENERAL_TIM_RCC_CLK_ENABLE();
  
 /* 基本定时器外设时钟使能 */
  htimx_GeneralTIM.Instance = GENERAL_TIMx;
  htimx_GeneralTIM.Init.Prescaler = GENERAL_TIM_PRESCALER;
  htimx_GeneralTIM.Init.CounterMode = TIM_COUNTERMODE_UP;
  htimx_GeneralTIM.Init.Period = GENERAL_TIM_PERIOD;
  htimx_GeneralTIM.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htimx_GeneralTIM);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htimx_GeneralTIM, &sClockSourceConfig);

  /* 从模式配置,IT1触发更新 */
  sslaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sslaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sslaveConfig.TriggerFilter = 0;
  sslaveConfig.TriggerPolarity = 0;
  sslaveConfig.TriggerPrescaler = 0;
  HAL_TIM_SlaveConfigSynchronization(&htimx_GeneralTIM,&sslaveConfig);
  
  sConfigIC.ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  HAL_TIM_IC_ConfigChannel(&htimx_GeneralTIM, &sConfigIC, GENERAL_TIM_CHANNEL1);
  
  sConfigIC.ICPolarity = GENERAL_TIM_END_ICPolarity;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  HAL_TIM_IC_ConfigChannel(&htimx_GeneralTIM, &sConfigIC, GENERAL_TIM_CHANNEL2);
}

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
