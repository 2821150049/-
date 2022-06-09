/**
  ******************************************************************************
  * �ļ�����: bsp_BasicTIM.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2017-03-30
  * ��    ��: ������ʱ��TIM6 & TIM7�ײ���������
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F4Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "GeneralTIM/bsp_GeneralTIM.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
TIM_HandleTypeDef htimx_GeneralTIM;
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

/**
  * ��������: ��ʱ��ͨ��1���ų�ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base == &htimx_GeneralTIM)
  {
    /* ������ʱ������ʱ��ʹ�� */
    GENERAL_TIM_RCC_CLK_ENABLE();
    GENERAL_TIMX_GPIO_RCC_CLK_ENABLE();
    GPIO_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = GENERAL_TIM_CH1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;     // ����ģʽ
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GENERAL_TIMx_GPIO_AF;
    HAL_GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStruct);
    
    /* ��������������� */   
    GPIO_InitStruct.Pin = PUL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = 0;        // GPIO��������TIM���ù���
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(PUL_PORT, &GPIO_InitStruct);
      
    /* ���ö�ʱ���ж����ȼ���ʹ�� */
    HAL_NVIC_SetPriority(GENERAL_TIM_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(GENERAL_TIM_IRQ);
  }
}
/**
  * ��������: ������ʱ����ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void GENERAL_TIMx_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_SlaveConfigTypeDef sslaveConfig;
  TIM_IC_InitTypeDef sConfigIC;
  
  GENERAL_TIM_RCC_CLK_ENABLE();
  
 /* ������ʱ������ʱ��ʹ�� */
  htimx_GeneralTIM.Instance = GENERAL_TIMx;
  htimx_GeneralTIM.Init.Prescaler = GENERAL_TIM_PRESCALER;
  htimx_GeneralTIM.Init.CounterMode = TIM_COUNTERMODE_UP;
  htimx_GeneralTIM.Init.Period = GENERAL_TIM_PERIOD;
  htimx_GeneralTIM.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htimx_GeneralTIM);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htimx_GeneralTIM, &sClockSourceConfig);

  /* ��ģʽ����,IT1�������� */
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

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
