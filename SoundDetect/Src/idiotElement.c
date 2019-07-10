#include <stdio.h>

#include "idiotElement.h"
#include "usart.h"
#include "cmsis_os.h"
//typedef struct dick{
//	short direction;
//	short speed;
//	short yaw;
//	short time;
//}idiotStruct

//char cmd[14] = {0xF5, 0x5F, 0x08, 0x02 ,0x08};
//idiotStruct move_struct;
extern UART_HandleTypeDef huart3;

char* cmd_write(short direction, short speed, short yaw, short time){
	int i;
	char check = 0;
	char* cmd = (char *)pvPortMalloc(CMD_SIZE);
  cmd[0] = 0xF5;
  cmd[1] = 0x5F;
  cmd[2] = 0x08;
  cmd[3] = 0x02;
  cmd[4] = 0x08;
	cmd[5] = direction & 0xFF;
	cmd[6] = direction >> 8;
	cmd[7] = speed & 0xFF;
  cmd[8] = speed >> 8;
	cmd[9] = yaw & 0xFF;
  cmd[10] = yaw >> 8;
	cmd[11] = time & 0xFF;
	cmd[12] = time >> 8;	
	for(i=2;i<13;i++)
		check = check + cmd[i];
	cmd[13] = 0xFF & ~check;
	return cmd;
}

int cmdSend(char * cmd){
//	usart_print(&huart3,cmd);
	usart_transmit_data(&huart3, cmd, CMD_SIZE);
	vPortFree(cmd);
	return F_SUCCESS;
}
//idiotStruct* move_func(){
//	move_struct.direction = direction;
//	move_struct.speed = speed;
//	move_struct.yaw = yaw;
//	move_struct.time = time;
//	
//	cmd_write(move_struct.direction,move_struct.speed,move_struct.yaw,move_struct.time);
//	uartsend(cmd);

//}
