/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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


#include "u_console.h"
#include "u_then.h"
#include "u_steer.h"
#include "u_motor.h"
#include "u_infrared.h"

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
#define INFRARED_7_Pin GPIO_PIN_3
#define INFRARED_7_GPIO_Port GPIOA
#define INFRARED_7_EXTI_IRQn EXTI3_IRQn
#define INFRARED_6_Pin GPIO_PIN_4
#define INFRARED_6_GPIO_Port GPIOA
#define INFRARED_6_EXTI_IRQn EXTI4_IRQn
#define INFRARED_5_Pin GPIO_PIN_5
#define INFRARED_5_GPIO_Port GPIOA
#define INFRARED_5_EXTI_IRQn EXTI9_5_IRQn
#define INFRARED_4_Pin GPIO_PIN_6
#define INFRARED_4_GPIO_Port GPIOA
#define INFRARED_4_EXTI_IRQn EXTI9_5_IRQn
#define INFRARED_3_Pin GPIO_PIN_7
#define INFRARED_3_GPIO_Port GPIOA
#define INFRARED_3_EXTI_IRQn EXTI9_5_IRQn
#define INFRARED_2_Pin GPIO_PIN_0
#define INFRARED_2_GPIO_Port GPIOB
#define INFRARED_2_EXTI_IRQn EXTI0_IRQn
#define INFRARED_1_Pin GPIO_PIN_1
#define INFRARED_1_GPIO_Port GPIOB
#define INFRARED_1_EXTI_IRQn EXTI1_IRQn
#define INFRARED_0_Pin GPIO_PIN_10
#define INFRARED_0_GPIO_Port GPIOB
#define INFRARED_0_EXTI_IRQn EXTI15_10_IRQn
#define MOTOR_1_Pin GPIO_PIN_8
#define MOTOR_1_GPIO_Port GPIOA
#define MOTOR_2_Pin GPIO_PIN_9
#define MOTOR_2_GPIO_Port GPIOA
#define MOTOR_3_Pin GPIO_PIN_10
#define MOTOR_3_GPIO_Port GPIOA
#define MOTOR_4_Pin GPIO_PIN_11
#define MOTOR_4_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
