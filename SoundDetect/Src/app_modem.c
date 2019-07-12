#include "app_modem.h"

#include "cmsis_os.h"

#include "msg.h"
#include "log.h"
//#include "data.h"

#include "timer.h"


extern osMessageQId modemQueueHandle;

static int modem_dsp_start(const TASK_MSG *msg)
{
		dsp_test();
	
}

static TASK_MSG_MAP modem_msgMap[] =
{
		{DSP_START,   modem_dsp_start},
};

void app_modem(void const * argument)
{
    TASK_MSG *pMsg = NULL;

    LOG_DEBUG("task modem start");

    while(1)
    {
        xQueueReceive(modemQueueHandle, &pMsg, portMAX_DELAY);
        msg_msgProc(pMsg, modem_msgMap, sizeof(modem_msgMap) / sizeof(modem_msgMap[0]));
    }
}

