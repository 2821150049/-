/**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2018-01-08
  * ��    ��: ��ʱ������������
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
#include "stm32f4xx_hal.h"
#include "led/bsp_led.h"
#include "GeneralTIM/bsp_GeneralTIM.h"
#include "usart/bsp_debug_usart.h"
#include "key/bsp_key.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
STRUCT_CAPTURE strCapture = { 0, 0, 0 };

/* ��չ���� ------------------------------------------------------------------*/
extern __IO uint32_t uwTick;
__IO uint16_t Toggle_Pulse = 0; // �������
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

/**
  * ��������: ϵͳʱ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
 
  __HAL_RCC_PWR_CLK_ENABLE();                                     //ʹ��PWRʱ��

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  //���õ�ѹ�������ѹ����1

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // �ⲿ����8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                        //��HSE 
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                    //��PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;            //PLLʱ��Դѡ��HSE
  RCC_OscInitStruct.PLL.PLLM = 8;                                 //8��ƵMHz
  RCC_OscInitStruct.PLL.PLLN = 336;                               //336��Ƶ
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     //2��Ƶ���õ�168MHz��ʱ��
  RCC_OscInitStruct.PLL.PLLQ = 7;                                 //USB/SDIO/������������ȵ���PLL��Ƶϵ��
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // ϵͳʱ�ӣ�168MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHBʱ�ӣ� 168MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1ʱ�ӣ�42MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2ʱ�ӣ�84MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_EnableCSS();                                            // ʹ��CSS���ܣ�����ʹ���ⲿ�����ڲ�ʱ��ԴΪ����
  
 	// HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ��
	// HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ��
	// HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ��
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);                // ���ò�����ϵͳ�δ�ʱ��
  /* ϵͳ�δ�ʱ��ʱ��Դ */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* ϵͳ�δ�ʱ���ж����ȼ����� */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/**
  * ��������: ������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
int main(void)
{
  __IO uint32_t ulTmrClk, ulTime;
  /* ��λ�������裬��ʼ��Flash�ӿں�ϵͳ�δ�ʱ�� */
  HAL_Init();
  /* ����ϵͳʱ�� */
  SystemClock_Config();
  
  /* ����LED��ʼ�� */
  LED_GPIO_Init();

  /* ��ʼ�����ڲ����ô����ж����ȼ� */
  MX_DEBUG_USART_Init();
  
  /* ͨ�ö�ʱ����ʼ�� */
  GENERAL_TIMx_Init();
  
  printf ( "STM32 ���벶��ʵ��\n" );
	printf ( "����KEY1������KEY1���µ�ʱ��\n" );
  
  /* ��ȡ��ʱ��ʱ������ */	
	ulTmrClk = GENERAL_TIM_FREQ()/(GENERAL_TIM_PRESCALER+1);    
  /* ������ʱ�� */
  HAL_TIM_Base_Start_IT(&htimx_GeneralTIM);  
  /* ������ʱ��ͨ�����벶�񲢿����ж� */
  HAL_TIM_IC_Start_IT(&htimx_GeneralTIM,GENERAL_TIM_CHANNEL1);
  Toggle_Pulse = 50;
  /* ����ѭ�� */
  while (1)
  {
    /* ��ɲ����͵�ƽ���� */
    if(strCapture.ucFinishFlag == 1 )
		{
      /* ����͵�ƽ����ֵ */
			ulTime = strCapture .usPeriod * GENERAL_TIM_PERIOD + strCapture .usCtr;
			/* ��ӡ�͵�ƽ����ʱ�� */
			printf ( ">>��õ͵�ƽ����ʱ�䣺%f s\n", ((float)ulTime / ulTmrClk ) ); 
			strCapture .ucFinishFlag = 0;			
		}
    if(KEY1_StateRead() == KEY_DOWN)
    {
      HAL_GPIO_WritePin(PUL_PORT,PUL_PIN,GPIO_PIN_RESET);
    }
    else 
      HAL_GPIO_WritePin(PUL_PORT,PUL_PIN,GPIO_PIN_SET);
  }
}

/**
  * ��������: ������ģʽ�¶�ʱ���Ļص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  strCapture .usPeriod ++;
}

/**
  * ��������: ��ʱ�����벶���жϻص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  TIM_IC_InitTypeDef sConfigIC;
  
  if ( strCapture .ucStartFlag == 0 )
  {
    LED1_TOGGLE;       
    
    __HAL_TIM_SET_COUNTER(htim,0); // ���㶨ʱ������
    strCapture .usPeriod = 0;			
    strCapture .usCtr = 0;
    
    // �������벶���������Ҫ���޸Ĵ�����ƽ
    sConfigIC.ICPolarity = GENERAL_TIM_END_ICPolarity;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(htim, &sConfigIC, GENERAL_TIM_CHANNEL1);
    // ����жϱ�־λ
    __HAL_TIM_CLEAR_IT(htim, GENERAL_TIM_IT_CC1);
    // �������벶�񲢿����ж�
    HAL_TIM_IC_Start_IT(htim,GENERAL_TIM_CHANNEL1);    
    strCapture .ucStartFlag = 1;			
  }		
  
  else
  {
    LED1_TOGGLE;
    
    // ��ȡ��ʱ������ֵ
    strCapture .usCtr = HAL_TIM_ReadCapturedValue(htim,GENERAL_TIM_CHANNEL1);
    // �������벶���������Ҫ���޸Ĵ�����ƽ
    sConfigIC.ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(htim, &sConfigIC, GENERAL_TIM_CHANNEL1);
    
    // ����жϱ�־λ
    __HAL_TIM_CLEAR_IT(htim, GENERAL_TIM_IT_CC1); 
    // �������벶�񲢿����ж�
    HAL_TIM_IC_Start_IT(htim,GENERAL_TIM_CHANNEL1);    
    strCapture .ucStartFlag = 0;			
    strCapture .ucFinishFlag = 1;    
  }
}


/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
