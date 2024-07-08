/* USER CODE BEGIN Header */
/*
    __                               __  __                  
   / /   ____ _ _____ ___   _____   / / / /____ _ _____ ____ 
  / /   / __ `// ___// _ \ / ___/  / /_/ // __ `// ___// __ \
 / /___/ /_/ /(__  )/  __// /     / __  // /_/ // /   / /_/ /
/_____/\__,_//____/ \___//_/     /_/ /_/ \__,_//_/   / .___/ 
                                                    /_/      
*/
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  * Authors: Ian Searle
  * Version: 1.0.0
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sine_tables.h" 

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* These defines represent the point in a list where that notes data is held.*/
#define NOTE_C 		0
#define NOTE_Cs 	1
#define NOTE_D 		2
#define NOTE_Ds 	3
#define NOTE_E 		4
#define NOTE_F 		5
#define NOTE_Fs 	6
#define NOTE_G 		7
#define NOTE_Gs 	8
#define NOTE_A 		9
#define NOTE_As		10
#define NOTE_B 		11


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac1;

TIM_HandleTypeDef htim15;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Index and Active are lists that are 12 long. This is to improve spatial locality in the program.
Using the above stated define we can thats notes data from the list*/
int index[]= {0,0,0,0,0,0,0,0,0,0,0,0};
int active[] = {1,0,0,0,0,0,0,0,0,0,0,0};

int wave_out= 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM15_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_DAC1_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim15); // Start the Music Interrupt Timer

  HAL_DAC_Start(&hdac1, DAC_CHANNEL_2); // Start one of the dac channels

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // No Main While needed
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */

  /** DAC Initialization
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief TIM15 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM15_Init(void)
{

  /* USER CODE BEGIN TIM15_Init 0 */

  /* USER CODE END TIM15_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM15_Init 1 */

  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 80-1;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 9;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */

  /* USER CODE END TIM15_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NOTE_1_Pin NOTE_2_Pin NOTE_3_Pin NOTE_4_Pin
                           NOTE_5_Pin NOTE_6_Pin NOTE_7_Pin NOTE_8_Pin
                           NOTE_9_Pin NOTE_10_Pin NOTE_11_Pin NOTE_12_Pin */
  GPIO_InitStruct.Pin = NOTE_1_Pin|NOTE_2_Pin|NOTE_3_Pin|NOTE_4_Pin
                          |NOTE_5_Pin|NOTE_6_Pin|NOTE_7_Pin|NOTE_8_Pin
                          |NOTE_9_Pin|NOTE_10_Pin|NOTE_11_Pin|NOTE_12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	switch (GPIO_Pin) {
	case NOTE_1_Pin:
		active[NOTE_C] = !active[NOTE_C];
		break;
	case NOTE_2_Pin:
		active[NOTE_Cs] = !active[NOTE_Cs];
		break;
	case NOTE_3_Pin:
		active[NOTE_D] = !active[NOTE_D];
		break;
	case NOTE_4_Pin:
		active[NOTE_Ds] = !active[NOTE_Ds];
		break;
	case NOTE_5_Pin:
		active[NOTE_E] = !active[NOTE_E];
		break;
	case NOTE_6_Pin:
		active[NOTE_F] = !active[NOTE_F];
		break;
	case NOTE_7_Pin:
		active[NOTE_Fs] = !active[NOTE_Fs];
		break;
	case NOTE_8_Pin:
		active[NOTE_G] = !active[NOTE_G];
		break;
	case NOTE_9_Pin:
		active[NOTE_Gs] = !active[NOTE_Gs];
		break;
	case NOTE_10_Pin:
		active[NOTE_A] = !active[NOTE_A];
		break;
	case NOTE_11_Pin:
		active[NOTE_As] = !active[NOTE_As];
		break;
	case NOTE_12_Pin:
		active[NOTE_B] = !active[NOTE_B];
		break;

	default:
		break;
	}
}

// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim15 )
  {
    /* ***************************************************************
    * This first batch of values is to look update the value for each Note.
    * By using a list and different indexs we can speed up the program with good spatial locality
    * If the note is active then we update the value. Otherwise we return a zero.
    ***************************************************************************/
	  int C_val = 	active[NOTE_C]?C_TABLE[index[NOTE_C]]:0;
	  int Cs_val = 	active[NOTE_Cs]?Cs_TABLE[index[NOTE_Cs]]:0;
	  int D_val = 	active[NOTE_D]?D_TABLE[index[NOTE_D]]:0;
	  int Ds_val = 	active[NOTE_Ds]?Ds_TABLE[index[NOTE_Ds]]:0;
	  int E_val = 	active[NOTE_E]?E_TABLE[index[NOTE_E]]:0;
	  int F_val = 	active[NOTE_F]?F_TABLE[index[NOTE_F]]:0;
	  int Fs_val = 	active[NOTE_Fs]?Fs_TABLE[index[NOTE_Fs]]:0;
	  int G_val = 	active[NOTE_G]?G_TABLE[index[NOTE_G]]:0;
	  int Gs_val = 	active[NOTE_Gs]?Gs_TABLE[index[NOTE_Gs]]:0;
	  int A_val = 	active[NOTE_A]?A_TABLE[index[NOTE_A]]:0;
	  int As_val = 	active[NOTE_As]?As_TABLE[index[NOTE_As]]:0;
	  int B_val = 	active[NOTE_B]?B_TABLE[index[NOTE_B]]:0;


    /* ***************************************************************
    This batch of code is to just update the index if the note is active.
    Since the active list should only ever hold a 0 or a 1, this code works. Avoid if statements
      ***************************************************************************/
	  index[NOTE_C] 	+= 	active[NOTE_C];
	  index[NOTE_Cs] 	+= 	active[NOTE_Cs];
	  index[NOTE_D]		+= 	active[NOTE_D];
	  index[NOTE_Ds] 	+= 	active[NOTE_Ds];
	  index[NOTE_E] 	+= 	active[NOTE_E];
	  index[NOTE_F] 	+= 	active[NOTE_F];
	  index[NOTE_Fs] 	+= 	active[NOTE_Fs];
	  index[NOTE_G] 	+= 	active[NOTE_G];
	  index[NOTE_Gs] 	+= 	active[NOTE_Gs];
	  index[NOTE_A] 	+= 	active[NOTE_A];
	  index[NOTE_As] 	+= 	active[NOTE_As];
	  index[NOTE_B] 	+= 	active[NOTE_B];

		wave_out = C_val + Cs_val + Ds_val + D_val + E_val + F_val + Fs_val
				+ G_val + Gs_val + A_val + As_val + B_val; // Calculate the Sum of the wave
		int temp_wave = wave_out * 12 / 1; // This is for debugging purposes. Also 12/4 is to create the new offset for only using 4 notes

		HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_12B_L, temp_wave); // Output the wave
		/****************************************************************
		 This final section of Code is to handle the reseting of each index.
		 *********************************************************************/
		if (index[NOTE_C] > C_SAMPLES)
			index[NOTE_C] = 0;
		if (index[NOTE_Cs] > Cs_SAMPLES)
			index[NOTE_Cs] = 0;
		if (index[NOTE_D] > D_SAMPLES)
			index[NOTE_D] = 0;
		if (index[NOTE_Ds] > Ds_SAMPLES)
			index[NOTE_Ds] = 0;
		if (index[NOTE_E] > E_SAMPLES)
			index[NOTE_E] = 0;
		if (index[NOTE_F] > F_SAMPLES)
			index[NOTE_F] = 0;
		if (index[NOTE_Fs] > Fs_SAMPLES)
			index[NOTE_Fs] = 0;
		if (index[NOTE_G] > G_SAMPLES)
			index[NOTE_G] = 0;
		if (index[NOTE_Gs] > Gs_SAMPLES)
			index[NOTE_Gs] = 0;
		if (index[NOTE_A] > A_SAMPLES)
			index[NOTE_A] = 0;
		if (index[NOTE_As] > As_SAMPLES)
			index[NOTE_As] = 0;
		if (index[NOTE_B] > B_SAMPLES)
			index[NOTE_B] = 0;

  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
