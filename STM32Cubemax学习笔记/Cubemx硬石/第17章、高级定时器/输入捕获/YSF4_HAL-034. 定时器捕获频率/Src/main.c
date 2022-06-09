/**
  ******************************************************************************
  * �ļ�����: main.c
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2018-01-17
  * ��    ��: ��ʱ����������Ƶ��
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
#define TIM_PSC_1MHz          83
#define TIM_PSC_8400KHz        9

/* ˽�б��� ------------------------------------------------------------------*/
__IO STRUCT_CAPTURE strCapture = { 0, 1, 0, 0, 0};

/* ��չ���� ------------------------------------------------------------------*/
extern __IO uint32_t uwTick;
int32_t Toggle_Pulse = 0; // �������
__IO int32_t ulCcr;
double fFreq;
int32_t ulTimClk;
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
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/100000);                // ���ò�����ϵͳ�δ�ʱ��
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

  /* ��ȡ��ʱ��ʱ������ */
	ulTimClk = GENERAL_TIM_FREQ()/(GENERAL_TIM_PRESCALER+1);

  /* ������ʱ�� */
  HAL_TIM_Base_Start_IT(&htimx_GeneralTIM);
  /* ������ʱ��ͨ�����벶�񲢿����ж� */
  HAL_TIM_IC_Start_IT(&htimx_GeneralTIM,GENERAL_TIM_CHANNEL1);
  Toggle_Pulse = 4000;    //40ms��תһ�ε�ƽ , ���125Hz������
  strCapture.ucFinishFlag = 0;
  strCapture.ucStartFlag = 0;
  /* ����ѭ�� */
  while (1)
  {
    /* ��ɲ����ߵ�ƽ���� */
    if(strCapture.ucFinishFlag == 1)
    {
      if(ulCcr != 0)
      {
        /* ����Ƶ�� Freq = 1/T ,T������; T = ��c*t = ��c/f , f�Ƕ�ʱ��Ƶ��,��c�ǲ���ֵ,Freq = f / ��c */
        fFreq =  (double)ulTimClk / (double)ulCcr  ;
      }
      /* ��ӡƵ�� */
      printf ( ">>Freq��%.4lf kHz\n", fFreq/1000) ;
      /* ������ʱ����Ƶֵ */
      if(fFreq <= 10000  ) // 10KHz
      {
        __HAL_TIM_SET_PRESCALER(&htimx_GeneralTIM,TIM_PSC_1MHz);
        ulTimClk = GENERAL_TIM_FREQ()/ (TIM_PSC_1MHz+1) ;
      }
      else // 400KHz 
      {
        __HAL_TIM_SET_PRESCALER(&htimx_GeneralTIM,TIM_PSC_8400KHz);
        ulTimClk = GENERAL_TIM_FREQ()/ (TIM_PSC_8400KHz+1) ;
      }
      strCapture .ucFinishFlag = 0;
    }
    /* ��������Ƶ�� */
    if(KEY1_StateRead() == KEY_DOWN )
    {
      Toggle_Pulse+=100;
    }
    if(KEY2_StateRead() == KEY_DOWN )
    {
      Toggle_Pulse-=100;
    }
  }
}
/**
  * ��������: �δ�ʱ���жϻص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��ת��ƽ,�������
  */
void HAL_SYSTICK_Callback()
{
  if( (uwTick%Toggle_Pulse) == 0 )
    HAL_GPIO_TogglePin(PUL_PORT,PUL_PIN);
}
/**
  * ��������: ������ģʽ�¶�ʱ���Ļص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(strCapture.ucStartFlag == 1)
    strCapture .sPeriod ++;
}

/**
  * ��������: ��ʱ�����벶���жϻص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if(strCapture.ucStartFlag == 0 )
  {
    // ��ȡ��ʱ������ֵ
    strCapture .sLastCtr = HAL_TIM_ReadCapturedValue(htim,GENERAL_TIM_CHANNEL1);
    /* ���������� */
    strCapture .sPeriod = 0;
    strCapture.ucStartFlag = 1;
  }
  else if(strCapture.ucStartFlag == 1 )
  {
    strCapture.sCtr = HAL_TIM_ReadCapturedValue(htim,GENERAL_TIM_CHANNEL1);
    /* ���ǰ�����������صĲ���ֵ��ֵ */
    ulCcr = strCapture .sPeriod * (int32_t)GENERAL_TIM_PERIOD + (strCapture .sCtr - strCapture .sLastCtr);
    strCapture.ucFinishFlag = 1;
    strCapture.ucStartFlag = 0;
    LED1_TOGGLE;
  }
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
