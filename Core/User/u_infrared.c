/*
 * @Author: XLxiaoliao
 * @Date: 2023-03-29 22:22:31
 * @LastEditTime: 2023-04-05 22:21:52
 * @FilePath: \MDK-ARMd:\stm32\project\tmp1\Core\User\u_infrared.c
 */
#include "u_infrared.h"

Infrared_Typedef Infrared;

void Infrared_Init(void) {
    Infrared.is_collecting = 0; 
}

void Infrared_AfterCollecting(void) {
    Infrared.is_collecting = 0; 
    // 处理采集到的次数
    for (int i=0; i<8; i++) {
        Console_Log("%d -> %d", i, Infrared.trigger_count[i]);
    }
    // Console_Log("[0:7]: %d %d %d %d %d %d %d %d",
    //                                         Infrared.trigger_count[0],
    //                                         Infrared.trigger_count[1],
    //                                         Infrared.trigger_count[2],
    //                                         Infrared.trigger_count[3],
    //                                         Infrared.trigger_count[4],
    //                                         Infrared.trigger_count[5],
    //                                         Infrared.trigger_count[6],
    //                                         Infrared.trigger_count[7]);
}

void Infrared_Collect(void) {
    // 采集次数置零
    for (int i=0; i<8; i++) {
        Infrared.trigger_count[i] = 0;
    }
    // 正在采集
    Infrared.is_collecting = 1;
    // 一段时间后采集位置0
    Then_Work(100, Infrared_AfterCollecting);
}

// void Infrared_Collect(void) {
//     // 正在采集
//     Infrared.is_collecting = 1;
//     // 临时 有INFRARED_ROUND_PER_COLLECTION组数据 每组数据有8个
//     uint8_t tmp[8] = {0};
//     // 本轮采集完成标志位
//     uint8_t round_finish = 0;
//     // 采集多轮
//     for(int i=0; i<INFRARED_ROUND_PER_COLLECTION; i++) {
//         // 延迟一段时间后 本轮采集完成标志位置零
//         Then_Work(INFRARED_TIME_PER_ROUNS, Infrared_ResetIsCollecting);
//         round_finish = 0;
//         // 正在采集标志位置零 并且 至少完成一轮采集 才结束
//         while (Infrared.is_collecting && !round_finish) {
//             tmp[0] += HAL_GPIO_ReadPin(INFRARED_0_GPIO_Port, INFRARED_0_Pin);
//             tmp[1] += HAL_GPIO_ReadPin(INFRARED_1_GPIO_Port, INFRARED_1_Pin);
//             tmp[2] += HAL_GPIO_ReadPin(INFRARED_2_GPIO_Port, INFRARED_2_Pin);
//             tmp[3] += HAL_GPIO_ReadPin(INFRARED_3_GPIO_Port, INFRARED_3_Pin);
//             tmp[4] += HAL_GPIO_ReadPin(INFRARED_4_GPIO_Port, INFRARED_4_Pin);
//             tmp[5] += HAL_GPIO_ReadPin(INFRARED_5_GPIO_Port, INFRARED_5_Pin);
//             tmp[6] += HAL_GPIO_ReadPin(INFRARED_6_GPIO_Port, INFRARED_6_Pin);
//             tmp[7] += HAL_GPIO_ReadPin(INFRARED_7_GPIO_Port, INFRARED_7_Pin);
//             // 完成一轮采集
//             round_finish = 1;
//         }
//     }
//     // 若某个方向上采集到数据超过一半 说明有信号
//     for (int i=0; i<8; i++) {
//         Infrared.states[i] = (tmp[i] > INFRARED_COLLECTION_THRESHOLD)?0:1;
//     }
//     for (int i=0; i<8; i++) {
//         Console_Log("%d .. %d", Infrared.states[i], tmp[i]);
//     }
// }

void Infrared_Trigger_Handler(uint8_t index) {
    Infrared.trigger_count[index]++;
}
