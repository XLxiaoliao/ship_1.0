/*
 * @Author: XLxiaoliao
 * @Date: 2023-03-30 09:29:32
 * @LastEditTime: 2023-04-09 16:11:14
 * @FilePath: \MDK-ARMd:\stm32\project\ship_1.0\Core\User\u_steer.h
 */
#ifndef __U_STEER_H
#define __U_STEER_H

#include "main.h"

#define STEER_DEG_MIN 10
#define STEER_DEG_MAX 170

typedef struct
{
    TIM_HandleTypeDef *tim;
    uint32_t channel;
    int nowAngle;
    int targetAngle;
    uint8_t timeStep;

} Steer_Typedef;

void Steer_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void Steer_Set(int angle);
// void Steer_Stepping(void);

#endif
