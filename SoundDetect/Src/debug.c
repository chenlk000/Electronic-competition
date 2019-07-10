/*
 * debug.c
 *
 *  Created on: 2018年5月21日
 *      Author: wyb
 */
#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"

#include "debug.h"
#include "log.h"
#include "idiotElement.h"

#define MAX_BLOCKSIZE   128
#define MAX_CMD_LENGTH (16)
#define MAX_CMD_NUMBER  (32)
extern TIM_HandleTypeDef htim3;

typedef int (*CMD_ACTION)(const unsigned char* cmdString, unsigned short length);

typedef struct
{
    unsigned char cmd[MAX_CMD_LENGTH];
    CMD_ACTION  action;
} CMD_MAP;

#define DBG_OUT(fmt, ...) log_print("[DEBUG]>"fmt, ##__VA_ARGS__);log_print("\r\n")


static int cmd_debug(const unsigned char* cmdString, unsigned short length);

static int cmd_AT(const unsigned char* cmdString, unsigned short length)
{
    LOG_DEBUG("OK");
    return F_SUCCESS;
}

static int cmd_flash(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}

static int cmd_data(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}

static int cmd_setting(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}

static int cmd_start(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}

static int cmd_stop(const unsigned char *cmdString, unsigned short length)
{
//    data_setIsStart(L_FALSE);
    return F_SUCCESS;
}

static int cmd_get(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}


static int cmd_led(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}

static int cmd_dog(const unsigned char *cmdString, unsigned short length)
{

    return F_FAILED;
}

static int cmd_math(const unsigned char *cmdString, unsigned short length)
{
//		float32_t Ak[MAX_BLOCKSIZE] = {0,0,1,1,1,0,0};        /* Input A */
//		float32_t Bk[MAX_BLOCKSIZE] = {1,2,1};        /* Input B */
//		float32_t AxB[MAX_BLOCKSIZE * 2];   /* Output */
		int i,j;
	
		const float32_t xRef_f16[4] = {1,1,1,1};
		const float32_t yRef_f16[4] = {1,2,3,4};
		float32_t AB_f32[16];
		arm_status status;
		
		arm_matrix_instance_f32 X;      /* Matrix A Instance */
		arm_matrix_instance_f32 Y;     /* Matrix AT(A transpose) instance */
		arm_matrix_instance_f32 XY;   /* Matrix ATMA( AT multiply with A) instance */
		uint32_t srcRows, srcColumns; /* Temporary variables */
		srcRows = 4;
		srcColumns = 4;
		
		arm_mat_init_f32(&Y, 1, srcColumns, (float32_t *)xRef_f16);
		arm_mat_init_f32(&X, srcRows, 1, (float32_t *)yRef_f16);
		arm_mat_init_f32(&XY, srcRows, srcColumns, (float32_t *)AB_f32);
		
		status = arm_mat_mult_f32(&X, &Y, &XY);
		
		LOG_PRINT("status = %d",status);
		for(i=0;i<XY.numRows;i++){
			for(j=0;j<XY.numCols;j++){
			LOG_PRINT("XY[%d][%d] = %4f",i,j,*(XY.pData+j*XY.numCols+i));
			}
		}
		
		
    LOG_PRINT("multiple ok");
    return F_FAILED;
}

static int cmd_dds(const unsigned char *cmdString, unsigned short length)
{
	return F_FAILED;
}
static int cmd_move(const unsigned char * cmdString, unsigned short length)
{
		int rc = 0;
		short direction,speed,yaw,time;
	  char * movecmd;
		rc = sscanf((char *)cmdString, "move:%d,%d,%d,%d", &direction, &speed, &yaw, &time);
		if(rc==4){
			movecmd = cmd_write(direction, speed, yaw, time);
			cmdSend(movecmd);
			return 0;
		}
		else{
			LOG_ERROR("MOVE PARAMETER ERROR\r\n");
			return 1;
		}
				
}


static CMD_MAP cmd_map[] =
{
        {"debug",       cmd_debug},
        {"AT",          cmd_AT},
        {"move",        cmd_move},
        {"flash",       cmd_flash},
        {"data",        cmd_data},
        {"setting",     cmd_setting},
        {"start",       cmd_start},
        {"stop",        cmd_stop},
        {"get",         cmd_get},
        {"math",        cmd_math},
        {"led",         cmd_led},
        {"dog",         cmd_dog},
        {"dds",         cmd_dds},
};


static int cmd_debug(const unsigned char* cmdString, unsigned short length)
{
    int i = 0;
    DBG_OUT("support cmd:");
    for (i = 0; i < sizeof(cmd_map) / sizeof(cmd_map[0]) && cmd_map[i].action; i++)
    {
        DBG_OUT("\t%s\t%p", cmd_map[i].cmd, cmd_map[i].action);
    }

    return F_SUCCESS;
}

int debug_proc(const unsigned char *cmdString, unsigned short length)
{
    int i = 0;

    const unsigned char *cmd = cmdString;

    for (i = 0; i < sizeof(cmd_map) / sizeof(cmd_map[0]) && cmd_map[i].action; i++)
    {
        if (strncmp((const char *)cmd, (const char *)cmd_map[i].cmd, strlen((const char *)cmd_map[i].cmd)) == 0)
        {
            return cmd_map[i].action(cmdString, length);
        }
    }

    LOG_INFO("CMD not processed");

    return F_FAILED;
}
