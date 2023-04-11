/*
 * @Author: XLxiaoliao
 * @Date: 2023-03-29 22:22:42
 * @LastEditTime: 2023-04-09 16:49:06
 * @FilePath: \MDK-ARMd:\stm32\project\ship_1.0\Core\User\u_infrared.h
 */
#ifndef __U_INFRARED_H
#define __U_INFRARED_H

#include "main.h"

typedef struct
{
    // 上次采集的结果
    uint8_t states[8];
    // 是否正在采集
    uint8_t is_collecting;
    // 采集到几次
    uint8_t trigger_count[8];
} Infrared_Typedef;

#define INFRARED_TIME_PER_ROUNS                 5
#define INFRARED_ROUND_PER_COLLECTION           100
#define INFRARED_COLLECTION_THRESHOLD           (INFRARED_ROUND_PER_COLLECTION / 2)

#define INFRARED_0_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_0_GPIO_Port, INFRARED_0_Pin) == GPIO_PIN_RESET)
#define INFRARED_1_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_1_GPIO_Port, INFRARED_1_Pin) == GPIO_PIN_RESET)
#define INFRARED_2_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_2_GPIO_Port, INFRARED_2_Pin) == GPIO_PIN_RESET)
#define INFRARED_3_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_3_GPIO_Port, INFRARED_3_Pin) == GPIO_PIN_RESET)
#define INFRARED_4_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_4_GPIO_Port, INFRARED_4_Pin) == GPIO_PIN_RESET)
#define INFRARED_5_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_5_GPIO_Port, INFRARED_5_Pin) == GPIO_PIN_RESET)
#define INFRARED_6_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_6_GPIO_Port, INFRARED_6_Pin) == GPIO_PIN_RESET)
#define INFRARED_7_READ_IS_LOW (HAL_GPIO_ReadPin(INFRARED_7_GPIO_Port, INFRARED_7_Pin) == GPIO_PIN_RESET)

void Infrared_Init(void);
void Infrared_Collect(void);
void Infrared_Trigger_Handler(uint8_t index);

#endif
