/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define NOTE_1_Pin GPIO_PIN_0
#define NOTE_1_GPIO_Port GPIOC
#define NOTE_1_EXTI_IRQn EXTI0_IRQn
#define NOTE_2_Pin GPIO_PIN_1
#define NOTE_2_GPIO_Port GPIOC
#define NOTE_2_EXTI_IRQn EXTI1_IRQn
#define NOTE_3_Pin GPIO_PIN_2
#define NOTE_3_GPIO_Port GPIOC
#define NOTE_3_EXTI_IRQn EXTI2_IRQn
#define NOTE_4_Pin GPIO_PIN_3
#define NOTE_4_GPIO_Port GPIOC
#define NOTE_4_EXTI_IRQn EXTI3_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define NOTE_5_Pin GPIO_PIN_4
#define NOTE_5_GPIO_Port GPIOC
#define NOTE_5_EXTI_IRQn EXTI4_IRQn
#define NOTE_6_Pin GPIO_PIN_5
#define NOTE_6_GPIO_Port GPIOC
#define NOTE_6_EXTI_IRQn EXTI9_5_IRQn
#define NOTE_7_Pin GPIO_PIN_6
#define NOTE_7_GPIO_Port GPIOC
#define NOTE_7_EXTI_IRQn EXTI9_5_IRQn
#define NOTE_8_Pin GPIO_PIN_7
#define NOTE_8_GPIO_Port GPIOC
#define NOTE_8_EXTI_IRQn EXTI9_5_IRQn
#define NOTE_9_Pin GPIO_PIN_8
#define NOTE_9_GPIO_Port GPIOC
#define NOTE_9_EXTI_IRQn EXTI9_5_IRQn
#define NOTE_10_Pin GPIO_PIN_9
#define NOTE_10_GPIO_Port GPIOC
#define NOTE_10_EXTI_IRQn EXTI9_5_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define NOTE_11_Pin GPIO_PIN_10
#define NOTE_11_GPIO_Port GPIOC
#define NOTE_11_EXTI_IRQn EXTI15_10_IRQn
#define NOTE_12_Pin GPIO_PIN_11
#define NOTE_12_GPIO_Port GPIOC
#define NOTE_12_EXTI_IRQn EXTI15_10_IRQn
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
