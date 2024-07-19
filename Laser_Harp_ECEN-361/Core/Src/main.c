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
  * Authors: Ian Searle, Marshall Potts
  * Version: 1.0.0
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "sine_tables.h"
#include "tranposition.h"
#include "I2C_commands.h"
#include "screen.h"
#include "menu.h"
#include "sustain.h"

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

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Index and Active are lists that are 12 long. This is to improve spatial locality in the program.
Using the above stated define we can thats notes data from the list*/

int my_index[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int active[] = {0,0,0,0,0,0,0,0,0,0,0,0};

//variables to signify whether the note named should be sustained. Used in sustain.c
int sustain_C = 0;
int sustain_Cs = 0;
int sustain_D = 0;
int sustain_Ds = 0;
int sustain_E = 0;
int sustain_F = 0;
int sustain_Fs = 0;
int sustain_G = 0;
int sustain_Gs = 0;
int sustain_A = 0;
int sustain_As = 0;
int sustain_B = 0;


//char screen_out[] ={"H","e","l","l","o"};



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM15_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM16_Init(void);
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
  MX_I2C1_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim15); // Start the Music Interrupt Timer
  HAL_TIM_Base_Start_IT(&htim16); // Star the Sustain Interrupt Timer

  HAL_DAC_Start(&hdac1, DAC_CHANNEL_2); // Start one of the dac channels
  HAL_DAC_Start(&hdac1, DAC_CHANNEL_1); // Start one of the dac channels


  tranposition__increment_octave();
  menu_init();
  lcd_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  poll_buttons();
	  HAL_Delay(50);

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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10909CEC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 3200-1;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 100-1;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

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

  /*Configure GPIO pins : NOTE_1_Pin NOTE_2_Pin NOTE_3_Pin NOTE_4_Pin
                           NOTE_5_Pin NOTE_6_Pin NOTE_7_Pin NOTE_8_Pin
                           NOTE_9_Pin NOTE_10_Pin NOTE_11_Pin NOTE_12_Pin */
  GPIO_InitStruct.Pin = NOTE_1_Pin|NOTE_2_Pin|NOTE_3_Pin|NOTE_4_Pin
                          |NOTE_5_Pin|NOTE_6_Pin|NOTE_7_Pin|NOTE_8_Pin
                          |NOTE_9_Pin|NOTE_10_Pin|NOTE_11_Pin|NOTE_12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : TOP_BTN_Pin BOTTOM_BTN_Pin LEFT_BTN_Pin RIGHT_BTN_Pin */
  GPIO_InitStruct.Pin = TOP_BTN_Pin|BOTTOM_BTN_Pin|LEFT_BTN_Pin|RIGHT_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
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
	switch (GPIO_Pin) {

	// check if laser is broken and toggle with changes in laser state (rising and falling edge)
	// set flag for the sustain of each note with each activation



	case NOTE_1_Pin:
		if(HAL_GPIO_ReadPin(NOTE_1_GPIO_Port, NOTE_1_Pin) == 0)
		{
			active[NOTE_C] = 1;
			sustain_C = 1; // set flag for sustaining note. flag is reset in the sustain.c file after ~ 10s.
		}
		else
		{
			active[NOTE_C] = 0;
			sustain_C = 0;
		}
		//active[NOTE_C] = !active[NOTE_C];

		break;

	case NOTE_2_Pin:
		if(HAL_GPIO_ReadPin(NOTE_2_GPIO_Port, NOTE_2_Pin) == 0)
		{
			active[NOTE_Cs] = 1;
			sustain_Cs = 1;
		}
		else
		{
			active[NOTE_Cs] = 0;
			sustain_Cs = 0;
		}
		//active[NOTE_Cs] = !active[NOTE_Cs];
		break;

	case NOTE_3_Pin:
		if(HAL_GPIO_ReadPin(NOTE_3_GPIO_Port, NOTE_3_Pin) == 0)
		{
			active[NOTE_D] = 1;
			sustain_D = 1;
		}
		else
		{
			active[NOTE_D] = 0;
			sustain_D = 0;
		}
		break;

	case NOTE_4_Pin:
		if(HAL_GPIO_ReadPin(NOTE_4_GPIO_Port, NOTE_4_Pin) == 0)
		{
			active[NOTE_Ds] = 1;
			sustain_Ds = 1;
		}
		else
		{
			active[NOTE_Ds] = 0;
			sustain_Ds = 0;
		}
		//active[NOTE_Ds] = !active[NOTE_Ds];
		break;

	case NOTE_5_Pin:
		if(HAL_GPIO_ReadPin(NOTE_5_GPIO_Port, NOTE_5_Pin) == 0)
		{
			active[NOTE_E] = 1;
			sustain_E = 1;
		}
		else
		{
			active[NOTE_E] = 0;
			sustain_E = 0;
		}
		//active[NOTE_E] = !active[NOTE_E];
		break;

	case NOTE_6_Pin:
		if(HAL_GPIO_ReadPin(NOTE_6_GPIO_Port, NOTE_6_Pin) == 0)
		{
			active[NOTE_F] = 1;
			sustain_F = 1;
		}
		else
		{
			active[NOTE_F] = 0;
			sustain_F = 0;
		}
		//active[NOTE_F] = !active[NOTE_F];
		break;

	case NOTE_7_Pin:
		if(HAL_GPIO_ReadPin(NOTE_7_GPIO_Port, NOTE_7_Pin) == 0)
		{
			active[NOTE_Fs] = 1;
			sustain_Fs = 1;
		}
		else
		{
			active[NOTE_Fs] = 0;
			sustain_Fs = 0;
		}
		//active[NOTE_Fs] = !active[NOTE_Fs];
		break;

	case NOTE_8_Pin:
		if(HAL_GPIO_ReadPin(NOTE_8_GPIO_Port, NOTE_8_Pin) == 0)
		{
			active[NOTE_G] = 1;
			sustain_G = 1;
		}
		else
		{
			active[NOTE_G] = 0;
			sustain_G = 0;
		}
		//active[NOTE_G] = !active[NOTE_G];
		break;

	case NOTE_9_Pin:
		if(HAL_GPIO_ReadPin(NOTE_9_GPIO_Port, NOTE_9_Pin) == 0)
		{
			active[NOTE_Gs] = 1;
			sustain_Gs = 1;
		}
		else
		{
			active[NOTE_Gs] = 0;
			sustain_Gs = 0;
		}
		//active[NOTE_Gs] = !active[NOTE_Gs];
		break;

	case NOTE_10_Pin:
		if(HAL_GPIO_ReadPin(NOTE_10_GPIO_Port, NOTE_10_Pin) == 0)
		{
			active[NOTE_A] = 1;
			sustain_A = 1;
		}
		else
		{
			active[NOTE_A] = 0;
			sustain_A = 0;
		}
		//active[NOTE_A] = !active[NOTE_A];
		break;

	case NOTE_11_Pin:
		if(HAL_GPIO_ReadPin(NOTE_11_GPIO_Port, NOTE_11_Pin) == 0)
		{
			active[NOTE_As] = 1;
			sustain_As = 1;
		}
		else
		{
			active[NOTE_As] = 0;
			sustain_As = 0;
		}
		//active[NOTE_As] = !active[NOTE_As];
		break;

	case NOTE_12_Pin:
		if(HAL_GPIO_ReadPin(NOTE_12_GPIO_Port, NOTE_12_Pin) == 0)
		{
			active[NOTE_B] = 1;
			sustain_B = 1;
		}
		else
		{
			active[NOTE_B] = 0;
			sustain_B = 0;
		}
		//active[NOTE_B] = !active[NOTE_B];
		break;

	default:
		break;
	}
}

// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//timer for sustain value update at 25kHz sample rate
	if(htim == &htim16 )
	{
		// update the decay value for each note at 250Hz
		update_decay_values();
	}

	if (htim == &htim15 )
	{
		//Disable the IRQ
		//HAL_TIM_Base_Stop(htim);
		int wave = tranposition__note_update();
		//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_L, wave);
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, wave);
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wave);
		//HAL_TIM_Base_Start_IT(&htim15);
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
