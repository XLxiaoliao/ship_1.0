/*
 * @Author: XLxiaoliao
 * @Date: 2023-03-28 23:02:04
 * @LastEditTime: 2023-04-09 15:53:24
 * @FilePath: \MDK-ARMd:\stm32\project\ship_1.0\Core\User\u_then.c
 */
#include "u_then.h"

Then_Typedef u_then_obj;

/**
 * @description: 初始化 在完成功能前必须要调用此函数
 * @param {TIM_HandleTypeDef} *htim
 * @return {*}
 */
void Then_Init(TIM_HandleTypeDef *htim)
{
    u_then_obj.tim = htim;
    u_then_obj.is_working = 0;
}
/**
 * @description: 查找一个空闲的工作模块id 此操作不更新is_full
 * @return {*} 空闲的线路的最小id 若无则返回-1
 */

int Then_Find_Free(void)
{
    int index = -1;
    int i = 0;
    for (; i<U_THEN_MAX_WORK_NUM; i++)
    {
        if (!u_then_obj.count[i])
        {
            index = i;
            break;
        }        
    }
    return index;
}
/**
 * @description: then 延迟若干个计数器周期后执行
 * @param {int} ms
 * @return {*}
 */
int Then_Work(int timesOfPeriod, void(*funct)(void))
{
    int index;
    index = Then_Find_Free();
    if (index == -1)
    {
        return -1;
    }
    u_then_obj.count[index] = timesOfPeriod;
    u_then_obj.u_then_function[index] = funct;
    u_then_obj.is_working = 1;
    HAL_TIM_Base_Start_IT(u_then_obj.tim);
    return index;
}

void Then_Interrupt_Handler(void) {
    // 标记是否有计数器在工作状态
    int flag = 0;
    // 将所有工作中的线路count减一
    for(int i=0; i<U_THEN_MAX_WORK_NUM; i++)
    {
      if(u_then_obj.count[i])
      {
        u_then_obj.count[i] --;
        flag = 1;
        if(!u_then_obj.count[i])
        {
          // 若减完后变为0 则触发函数
          (*u_then_obj.u_then_function[i])();
        }
      }
    }
    if(!flag)
    {
      // 若都没有工作中的通道 则关闭定时器
      HAL_TIM_Base_Stop_IT(u_then_obj.tim);
    }
}

/* END */
