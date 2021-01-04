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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENC_1_Pin GPIO_PIN_0
#define ENC_1_GPIO_Port GPIOC
#define ENC_2_Pin GPIO_PIN_1
#define ENC_2_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_6
#define LED_RED_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOB
#define MOTOR_H5_Pin GPIO_PIN_14
#define MOTOR_H5_GPIO_Port GPIOB
#define MOTOR_H6_Pin GPIO_PIN_15
#define MOTOR_H6_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOC
#define MODE_BTN_Pin GPIO_PIN_9
#define MODE_BTN_GPIO_Port GPIOC
#define BackEMF_Pin GPIO_PIN_4
#define BackEMF_GPIO_Port GPIOB
#define MOTOR_H1_Pin GPIO_PIN_6
#define MOTOR_H1_GPIO_Port GPIOB
#define MOTOR_H2_Pin GPIO_PIN_7
#define MOTOR_H2_GPIO_Port GPIOB
#define MOTOR_H3_Pin GPIO_PIN_8
#define MOTOR_H3_GPIO_Port GPIOB
#define MOTOR_H4_Pin GPIO_PIN_9
#define MOTOR_H4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
