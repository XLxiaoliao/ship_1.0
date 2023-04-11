/*
 * @Author: XLxiaoliao
 * @Date: 2023-03-30 09:29:18
 * @LastEditTime: 2023-04-09 16:21:49
 * @FilePath: \MDK-ARMd:\stm32\project\ship_1.0\Core\User\u_steer.c
 */
#include "u_steer.h"

Steer_Typedef Steer_Obj;
/**
 * @description: 初始化舵机 
 *              舵机的定时器参数应该为
 *                  分频800 
 *                  计数1800 
 *                  CH Polarity High
 * @param {TIM_HandleTypeDef} *htim
 * @param {uint32_t} channel
 * @return {*}
 */
void Steer_Init(TIM_HandleTypeDef *htim, uint32_t channel) {
    Steer_Obj.tim = htim;
    Steer_Obj.channel = channel;
    Steer_Obj.nowAngle = 90;
    Steer_Obj.timeStep = 60;
    HAL_TIM_PWM_Start(Steer_Obj.tim, Steer_Obj.channel);
    Steer_Set(90);
}
void Steer_SetAngleDirectly(int angle) {
    Steer_Obj.nowAngle = angle;
    __HAL_TIM_SetCompare(Steer_Obj.tim, Steer_Obj.channel, angle + 45);
}
void Steer_Stepping(void) {
    int difference = Steer_Obj.targetAngle - Steer_Obj.nowAngle;
    // 若是增大角度 则直接执行
    if (difference > 0) {
        Steer_SetAngleDirectly(Steer_Obj.targetAngle);
        return;
    }
    if (difference < -10) {
        // 若与现在角度相差大于10 则只变化10度
        // 先减小10度
        Steer_SetAngleDirectly(Steer_Obj.nowAngle-10);
        // 一小段时间后再减小
        Then_Work(Steer_Obj.timeStep, Steer_Stepping);
    } else {
        // 若相差小于10 则直接设置
        Steer_SetAngleDirectly(Steer_Obj.targetAngle);
    }
}
/**
 * @description: 设置舵机角度
 * @param {int} angle
 * @return {*}
 */
void Steer_Set(int angle) {
    if(angle < STEER_DEG_MIN) {
        angle = STEER_DEG_MIN;
    }
    if(angle > STEER_DEG_MAX) {
        angle = STEER_DEG_MAX;
    }
    // 由于计数满值为1800 占空比0.025-0.125分别对应 45与225
    // 故此处赋值为 angle+45
    // __HAL_TIM_SetCompare(Steer_Obj.tim, Steer_Obj.channel, angle + 45);
    Steer_Obj.targetAngle = angle;
    Steer_Stepping();
}


