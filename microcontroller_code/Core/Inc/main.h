/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D12_9_Pin GPIO_PIN_14
#define D12_9_GPIO_Port GPIOG
#define D12_2_Pin GPIO_PIN_5
#define D12_2_GPIO_Port GPIOB
#define D12_0_Pin GPIO_PIN_4
#define D12_0_GPIO_Port GPIOB
#define D12_3_Pin GPIO_PIN_15
#define D12_3_GPIO_Port GPIOA
#define D12_10_Pin GPIO_PIN_13
#define D12_10_GPIO_Port GPIOG
#define RD_Pin GPIO_PIN_11
#define RD_GPIO_Port GPIOG
#define MCU_ACTIVE_Pin GPIO_PIN_12
#define MCU_ACTIVE_GPIO_Port GPIOG
#define CS_Pin GPIO_PIN_10
#define CS_GPIO_Port GPIOG
#define D12_4_Pin GPIO_PIN_13
#define D12_4_GPIO_Port GPIOC
#define D12_8_Pin GPIO_PIN_9
#define D12_8_GPIO_Port GPIOG
#define D12_6_Pin GPIO_PIN_7
#define D12_6_GPIO_Port GPIOC
#define D12_5_Pin GPIO_PIN_6
#define D12_5_GPIO_Port GPIOC
#define D12_7_Pin GPIO_PIN_13
#define D12_7_GPIO_Port GPIOB
#define BUSY_Pin GPIO_PIN_12
#define BUSY_GPIO_Port GPIOB
#define BUSY_EXTI_IRQn EXTI15_10_IRQn
#define D12_11_Pin GPIO_PIN_1
#define D12_11_GPIO_Port GPIOC
#define FRAME_RATE_Pin GPIO_PIN_1
#define FRAME_RATE_GPIO_Port GPIOA
#define VSYNC_FREQ_Pin GPIO_PIN_2
#define VSYNC_FREQ_GPIO_Port GPIOA
#define RENDER_TIME_Pin GPIO_PIN_6
#define RENDER_TIME_GPIO_Port GPIOA
#define D12_1_Pin GPIO_PIN_5
#define D12_1_GPIO_Port GPIOA
#define CONVST_Pin GPIO_PIN_7
#define CONVST_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
