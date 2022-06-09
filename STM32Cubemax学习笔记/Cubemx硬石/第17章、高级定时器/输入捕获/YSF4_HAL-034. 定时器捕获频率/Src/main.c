/**
  ******************************************************************************
  * 文件名程: main.c
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2018-01-17
  * 功    能: 定时器捕获脉冲频率
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
#include "stm32f4xx_hal.h"
#include "led/bsp_led.h"
#include "GeneralTIM/bsp_GeneralTIM.h"
#include "usart/bsp_debug_usart.h"
#include "key/bsp_key.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
#define TIM_PSC_1MHz          83
#define TIM_PSC_8400KHz        9

/* 私有变量 ------------------------------------------------------------------*/
__IO STRUCT_CAPTURE strCapture = { 0, 1, 0, 0, 0};

/* 扩展变量 ------------------------------------------------------------------*/
extern __IO uint32_t uwTick;
int32_t Toggle_Pulse = 0; // 脉宽控制
__IO int32_t ulCcr;
double fFreq;
int32_t ulTimClk;
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: 系统时钟配置
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();                                     //使能PWR时钟

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  //设置调压器输出电压级别1

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // 外部晶振，8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                        //打开HSE
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                    //打开PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;            //PLL时钟源选择HSE
  RCC_OscInitStruct.PLL.PLLM = 8;                                 //8分频MHz
  RCC_OscInitStruct.PLL.PLLN = 336;                               //336倍频
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     //2分频，得到168MHz主时钟
  RCC_OscInitStruct.PLL.PLLQ = 7;                                 //USB/SDIO/随机数产生器等的主PLL分频系数
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // 系统时钟：168MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHB时钟： 168MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1时钟：42MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2时钟：84MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_EnableCSS();                                            // 使能CSS功能，优先使用外部晶振，内部时钟源为备用

 	// HAL_RCC_GetHCLKFreq()/1000    1ms中断一次
	// HAL_RCC_GetHCLKFreq()/100000	 10us中断一次
	// HAL_RCC_GetHCLKFreq()/1000000 1us中断一次
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/100000);                // 配置并启动系统滴答定时器
  /* 系统滴答定时器时钟源 */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* 系统滴答定时器中断优先级配置 */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/**
  * 函数功能: 主函数.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
int main(void)
{

  /* 复位所有外设，初始化Flash接口和系统滴答定时器 */
  HAL_Init();
  /* 配置系统时钟 */
  SystemClock_Config();

  /* 板载LED初始化 */
  LED_GPIO_Init();

  /* 初始化串口并配置串口中断优先级 */
  MX_DEBUG_USART_Init();

  /* 通用定时器初始化 */
  GENERAL_TIMx_Init();

  printf ( "STM32 输入捕获实验\n" );

  /* 获取定时器时钟周期 */
	ulTimClk = GENERAL_TIM_FREQ()/(GENERAL_TIM_PRESCALER+1);

  /* 启动定时器 */
  HAL_TIM_Base_Start_IT(&htimx_GeneralTIM);
  /* 启动定时器通道输入捕获并开启中断 */
  HAL_TIM_IC_Start_IT(&htimx_GeneralTIM,GENERAL_TIM_CHANNEL1);
  Toggle_Pulse = 4000;    //40ms翻转一次电平 , 输出125Hz的脉冲
  strCapture.ucFinishFlag = 0;
  strCapture.ucStartFlag = 0;
  /* 无限循环 */
  while (1)
  {
    /* 完成测量高电平脉宽 */
    if(strCapture.ucFinishFlag == 1)
    {
      if(ulCcr != 0)
      {
        /* 脉冲频率 Freq = 1/T ,T是周期; T = Δc*t = Δc/f , f是定时器频率,Δc是捕获值,Freq = f / Δc */
        fFreq =  (double)ulTimClk / (double)ulCcr  ;
      }
      /* 打印频率 */
      printf ( ">>Freq：%.4lf kHz\n", fFreq/1000) ;
      /* 调整定时器分频值 */
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
    /* 按键调整频率 */
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
  * 函数功能: 滴答定时器中断回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 翻转电平,输出脉冲
  */
void HAL_SYSTICK_Callback()
{
  if( (uwTick%Toggle_Pulse) == 0 )
    HAL_GPIO_TogglePin(PUL_PORT,PUL_PIN);
}
/**
  * 函数功能: 非阻塞模式下定时器的回调函数
  * 输入参数: htim：定时器句柄
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(strCapture.ucStartFlag == 1)
    strCapture .sPeriod ++;
}

/**
  * 函数功能: 定时器输入捕获中断回调函数
  * 输入参数: htim：定时器句柄
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if(strCapture.ucStartFlag == 0 )
  {
    // 获取定时器计数值
    strCapture .sLastCtr = HAL_TIM_ReadCapturedValue(htim,GENERAL_TIM_CHANNEL1);
    /* 周期数清零 */
    strCapture .sPeriod = 0;
    strCapture.ucStartFlag = 1;
  }
  else if(strCapture.ucStartFlag == 1 )
  {
    strCapture.sCtr = HAL_TIM_ReadCapturedValue(htim,GENERAL_TIM_CHANNEL1);
    /* 获得前后两次上升沿的捕获值差值 */
    ulCcr = strCapture .sPeriod * (int32_t)GENERAL_TIM_PERIOD + (strCapture .sCtr - strCapture .sLastCtr);
    strCapture.ucFinishFlag = 1;
    strCapture.ucStartFlag = 0;
    LED1_TOGGLE;
  }
}

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
