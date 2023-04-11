/*
 * @Author: XLxiaoliao
 * @Date: 2023-03-28 21:24:19
 * @LastEditTime: 2023-04-09 16:36:34
 * @FilePath: \MDK-ARMd:\stm32\project\ship_1.0\Core\User\u_console.c
 */
#include "u_console.h"
#include "u_infrared.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern Motor_Typedef motor_1;
extern Motor_Typedef motor_2;
extern Steer_Typedef Steer_Obj;

Console_Typedef console;

int fputc(int ch, FILE *f)
{
  uint8_t tmp[1] = {ch};
  HAL_UART_Transmit(console.uart, tmp, 1, 0xffff);
  return ch;
}

int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(console.uart,&ch, 1, 0xffff);
  return ch;
}

void Console_Init(UART_HandleTypeDef *uart)
{
    console.length = 0;
    console.is_receiving = 0;
    console.uart = uart;
    // 打开串口接收中断
    HAL_UART_Receive_IT(uart, &console.buf, 1);
}

void Console_Log(const char *s, ...)
{
  va_list ap;
  // printf(strcat((char *)s,"\n"), ap);
  printf(s, ap);
  printf("\n");
}

void Console_Pre_Handler(void)
{
  // 将cmd的后几个填充为"\0"
  for(int i=console.length; i<U_CONSOLE_CMD_MAX_LENGTH; i++)
  {
    console.cmd[i] = 0;
  }
  Console_Log("recieve: %s", console.cmd);
  
  // 指令处理
  Console_Cmd_Handler();
  // 处理完后清空指令
  console.length = 0;
}

void Console_Receive_Handler(void)
{
  if(!console.is_receiving)
  {
    // 若没有在接收
    if(console.buf == U_CONSOLE_CMD_BEGIN_TAG)
    {
      // 若收到了初始字符 说明收到的是指令
      // 进入接收指令状态
      console.is_receiving = 1;
      // 长度置零
      console.length = 0;
    }
  }
  else
  {
    // 若正在接收
    if(console.buf == U_CONSOLE_CMD_END_TAG)
    {
      // 收到结束字符
      console.is_receiving = 0;
      // 处理命令
      Console_Pre_Handler();
    }
    else
    {
      if(console.length < U_CONSOLE_CMD_MAX_LENGTH)
      {
        // 若未接收完成 则填入
        console.cmd[console.length] = console.buf;
        console.length ++;
      }
      else
      {
        // 若满 发回错误提示 并且清空
        Console_Log("error:cmd_too_long");
        console.length = 0;
        console.is_receiving = 0;
      }
    }
  }
  HAL_UART_Receive_IT(console.uart, &console.buf, 1);
}

void Console_Cmd_Handler(void)
{
  char *head = strtok(console.cmd, " ");
  // 如果没有参数 arg会为null
  char *arg = strtok(NULL, " ");
  if (arg) {
		if (strcmp(head, "m1")==0) {
      Motor_Set(motor_1, atoi(arg));
    }
		if (strcmp(head, "m2")==0) {
      Motor_Set(motor_2, atoi(arg));
    }
		if (strcmp(head, "s")==0) {
      Steer_Set(atoi(arg));
    }
		if (strcmp(head, "s_set")==0) {
      Steer_Obj.timeStep = atoi(arg);
    }
  } else {
		if (strcmp(head, "c")==0) {
      Infrared_Collect();
    }
  }
}
