/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define Led_Red1_Pin GPIO_PIN_4
#define Led_Red1_GPIO_Port GPIOA
#define Led_Yellow1_Pin GPIO_PIN_5
#define Led_Yellow1_GPIO_Port GPIOA
#define Led_Green1_Pin GPIO_PIN_6
#define Led_Green1_GPIO_Port GPIOA
#define Led_Red2_Pin GPIO_PIN_7
#define Led_Red2_GPIO_Port GPIOA
#define Led_a1_Pin GPIO_PIN_0
#define Led_a1_GPIO_Port GPIOB
#define Led_b1_Pin GPIO_PIN_1
#define Led_b1_GPIO_Port GPIOB
#define Led_c1_Pin GPIO_PIN_2
#define Led_c1_GPIO_Port GPIOB
#define Led_d2_Pin GPIO_PIN_10
#define Led_d2_GPIO_Port GPIOB
#define Led_e2_Pin GPIO_PIN_11
#define Led_e2_GPIO_Port GPIOB
#define Led_f2_Pin GPIO_PIN_12
#define Led_f2_GPIO_Port GPIOB
#define Led_g2_Pin GPIO_PIN_13
#define Led_g2_GPIO_Port GPIOB
#define Led_Yellow2_Pin GPIO_PIN_8
#define Led_Yellow2_GPIO_Port GPIOA
#define Led_Green2_Pin GPIO_PIN_9
#define Led_Green2_GPIO_Port GPIOA
#define Led_d1_Pin GPIO_PIN_3
#define Led_d1_GPIO_Port GPIOB
#define Led_e1_Pin GPIO_PIN_4
#define Led_e1_GPIO_Port GPIOB
#define Led_f1_Pin GPIO_PIN_5
#define Led_f1_GPIO_Port GPIOB
#define Led_g1_Pin GPIO_PIN_6
#define Led_g1_GPIO_Port GPIOB
#define Led_a2_Pin GPIO_PIN_7
#define Led_a2_GPIO_Port GPIOB
#define Led_b2_Pin GPIO_PIN_8
#define Led_b2_GPIO_Port GPIOB
#define Led_c2_Pin GPIO_PIN_9
#define Led_c2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
