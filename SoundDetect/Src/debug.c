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

static int cmd_size(const unsigned char *cmdString, unsigned short length)
{


    LOG_ERROR("CMD error");
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

static int cmd_cnt(const unsigned char *cmdString, unsigned short length)
{

	
    LOG_ERROR("CMD error");
    return F_FAILED;
}

static int cmd_dds(const unsigned char *cmdString, unsigned short length)
{

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
        {"size",        cmd_size},
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
