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
STRUCT_CAPTURE strCapture = { 0, 0, 0, 0 };

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
  __IO uint32_t ulTmrClk, ulTime, ulDuty;
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
  
  printf ( "STM32 PWM���벶��ʵ��\n" );
	HAL_Delay(1000);
  
  /* ��ȡ��ʱ��ʱ������ */	
	ulTmrClk = GENERAL_TIM_FREQ()/(GENERAL_TIM_PRESCALER+1);    
  /* ������ʱ�� */
  HAL_TIM_Base_Start_IT(&htimx_GeneralTIM);  
  /* ������ʱ��ͨ�����벶�񲢿����ж� */
  HAL_TIM_IC_Start_IT(&htimx_GeneralTIM,GENERAL_TIM_CHANNEL1);
  HAL_TIM_IC_Start_IT(&htimx_GeneralTIM,GENERAL_TIM_CHANNEL2);
  Toggle_Pulse = 50;
  /* ����ѭ�� */
  while (1)
  {
    /* ��ɲ����ߵ�ƽ���� */
    if(strCapture.ucFinishFlag == 1 )
		{
      ulTime = strCapture.usPeriod ;
			/* ��ӡ����ʱ�� */
			printf ( ">>����������ڣ�%0.3f s\n", ((float)ulTime / ulTmrClk ) ); 
      
			ulTime = strCapture .usCtr;
			/* ��ӡ�͵�ƽ����ʱ�� */
			printf ( ">>�������ʱ�䣺%0.3f s\n", ((float)ulTime / ulTmrClk ) ); 

			strCapture .ucFinishFlag = 0;			
		}
  }
}
/**
  * ��������: �δ�ʱ���жϻص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_SYSTICK_Callback(void)
{
  if(uwTick % Toggle_Pulse == 0)
  {
    HAL_GPIO_TogglePin(PUL_PORT,PUL_PIN);
  }
}

/**
  * ��������: ��ʱ�����벶���жϻص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
  {
    LED1_TOGGLE;
    strCapture.usPeriod =  HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1)+1;
  }		
  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
  {
    LED1_TOGGLE;
    strCapture.usCtr =  HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_2)+1;
    strCapture.ucFinishFlag = 1;
  }
}
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
