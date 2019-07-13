#include "cmsis_os.h"
#include "msg.h"
#include "types.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include "log.h"
//#include "arm_math.h"

#define MSG_TIME_OUT 1000
#define MSG_D_TIME_OUT 1000

static int msgall_timeout(void);
extern TIM_HandleTypeDef htim3;
short data[3];
char captureFlag = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	
	if(htim->Instance->CNT==0 && captureFlag == 0){
		htim->Instance->CR1 |= 1<<0; //start counting 
	}
	if((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && !(captureFlag & HAL_TIM_ACTIVE_CHANNEL_1))
	{
		data[0] = htim->Instance->CCR1;
		log_print("CCR1 Captured\r\n");
	}else if((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)&& !(captureFlag & HAL_TIM_ACTIVE_CHANNEL_2)){
		data[1] = htim->Instance->CCR2;
		log_print("CCR2 Captured\r\n");

	}else if((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)&& !(captureFlag & HAL_TIM_ACTIVE_CHANNEL_3)){
		data[2] = htim->Instance->CCR3;
		log_print("CCR3 Captured\r\n");

	}
	captureFlag |= htim->Channel;
	if(captureFlag==(HAL_TIM_ACTIVE_CHANNEL_1|HAL_TIM_ACTIVE_CHANNEL_2|HAL_TIM_ACTIVE_CHANNEL_3)){
		TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1|TIM_CHANNEL_2|TIM_CHANNEL_3, TIM_CCx_DISABLE);
		timer_start(TIMER_MSGALL_TIMEOUT, MSG_TIME_OUT, msgall_timeout);
		
	}
//	htim->Instance->DIER &= ~(TIM_IT_UPDATE);
}

static int msgall_timeout(void)
{
	
    htim3.Instance->CNT = 0;
		htim3.Instance->CR1 &= 0;
		captureFlag = 0;
		msg_sendData(APP_MAIN,MSGALL_ARRIVE,(u8 *)data,6);
		TIM_CCxChannelCmd(htim3.Instance, TIM_CHANNEL_1|TIM_CHANNEL_2|TIM_CHANNEL_3, TIM_CCx_ENABLE);
    return F_SUCCESS;
}


//static int msgall_process(TASK_MSG *pMsg){

//}
