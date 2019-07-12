#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "app_main.h"
#include "log.h"
#include "msg.h"
#include "debug.h"
#include "usart.h"
//#include "flash.h"
//#include "data.h"
//#include "version.h"
//#include "uart_fpga.h"
//#include "uart_wifi.h"
//#include "led.h"
#include "timer.h"
//#include "spi_dds.h"

extern osMessageQId mainQueueHandle;
//extern IWDG_HandleTypeDef hiwdg;

static int main_usart1Recv(const TASK_MSG *msg)
{
    LOG_DEBUG("usart1 recieve %d bytes, data: %s", msg->length, msg->data);
#ifdef DEBUG
    debug_proc(msg->data, msg->length);
#endif
    return F_SUCCESS;
}

static int main_usart2Recv(const TASK_MSG *msg)
{
    LOG_DEBUG("bluetooth recieve %d bytes, data: ", msg->length);
    LOG_HEX(msg->data, msg->length);
//    uart_wifi_proc(msg->data, msg->length);

    return F_SUCCESS;
}

static int main_usart3Recv(const TASK_MSG *msg)
{
    LOG_DEBUG("usart3 recieve %d bytes", msg->length);
    // LOG_HEX((char *)msg->data, msg->length);
//    uart_fpga_input(msg->data, msg->length);
    return F_SUCCESS;
}

static int main_usart4Recv(const TASK_MSG *msg){
	return F_SUCCESS;
}
static int main_usart5Recv(const TASK_MSG *msg){
	return F_SUCCESS;
}



static int main_msgproc(const TASK_MSG *msg){
	
	short t1,t2,t3;
	
	t1 = msg->data[0] + (msg->data[1]<<8);
	t2 = msg->data[2] + (msg->data[3]<<8);
	t3 = msg->data[4] + (msg->data[5]<<8);
	
	LOG_DEBUG("delta12 = %f ms, delta23 = %f ms, delta13 = %f ms\r\n",\
//		(double)delta12/14000,(double)delta23/14000,(double)delta13/14000);
			(float)(t1-t2)/2.8f,(float)(t2-t3)/2.8,(float)(t1-t3)/2.8);

	return F_SUCCESS;
}

static TASK_MSG_MAP main_msgMap[] =
{
    {USART1_RECV,               main_usart1Recv},
    {USART2_RECV,               main_usart2Recv},
    {USART3_RECV,               main_usart3Recv},
    {USART4_RECV,               main_usart4Recv},
    {USART5_RECV,               main_usart5Recv},
		{MSGALL_ARRIVE,							main_msgproc},

};

int stm32_init(void)
{
//    LOG_DEBUG("stm32f405vgt6 version: "VERSION_STR);
    usart_init();
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
    //flash_init();
    return F_SUCCESS;
}

static int watchdogTimerCb(void)
{
    msg_sendCmd(APP_MAIN, FEED_DOG);
    timer_start(TIMER_WATCHDOG, 1000, watchdogTimerCb);
    return F_SUCCESS;
}

void app_main(void const * argument)
{
    TASK_MSG *pMsg = NULL;

    LOG_DEBUG("task main start");

    while(1)
    {
        xQueueReceive(mainQueueHandle, &pMsg, portMAX_DELAY);
        msg_msgProc(pMsg, main_msgMap, sizeof(main_msgMap) / sizeof(main_msgMap[0]));
    }
}

