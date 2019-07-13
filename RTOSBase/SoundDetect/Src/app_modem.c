#include "app_modem.h"

#include "cmsis_os.h"

#include "msg.h"
#include "log.h"
//#include "data.h"

#include "timer.h"


extern osMessageQId modemQueueHandle;

static int modem_measureStart(const TASK_MSG *msg)
{
//    DATA *pData = NULL;
//    SETTING *pSetting = NULL;
//    int i = 1;
//    int j = 0;
//    float error = 0;
//    int index = 0;
//    Complex result = {0};
//    u8 averageNum = 0;
//    u8 ignoreNum = 0;

//    if (L_TRUE == data_isScram())
//    {
//        data_setIsStart(L_FALSE);
//        return F_FAILED;
//    }

//    pData = data_getData();
//    averageNum = data_getAverageNum();
//    ignoreNum = data_getIgnoreNum();

//    pSetting = data_getSetting();

//    pData->curFre = pSetting->startFre;
//    pData->divFre = 1;
//    data_setIsStart(L_TRUE);
//    pData->isFirst = L_TRUE;

//    index = pSetting->currentIndex + 1;
//    if (index > BLOCK_NUM - 1)
//    {
//        index = 1;
//    }

//    if (F_FAILED == flash_eraseDataBlock(pSetting->blockAddress[index], BLOCK_DATA_SIZE / BLOCK_MAX_SIZE))
//    {
//        LOG_ERROR("data erase error");
//        return F_FAILED;
//    }

//    pSetting->blockSize[index] = 0;

//    led_start();

//    flash_write(pSetting->blockAddress[index] + pSetting->blockSize[index], pSetting, sizeof(SETTING));
//    pSetting->blockSize[index] += sizeof(SETTING);

//    dds_waveSeting(10, 0, SIN_WAVE, 0);

//    uart_wifi_sendSetting(pSetting);

//    timer_start(TIMER_DELAY, 3000, NULL);
//    while(L_TRUE == timer_isTimerStart(TIMER_DELAY))
//    {
//        osDelay(100);
//    }

//    LOG_DEBUG("start measure");

//    while (L_TRUE == pData->isStart && L_FALSE == data_isScram())
//    {
//        if(F_SUCCESS != get_fre(0))
//        {
//            pData->isStart = L_FALSE;
//            msg_sendCmd(APP_MODEM, MEASURE_SUCCESS);
//            return F_SUCCESS;
//        }

//        error = FPGA_SYSTEM_TICK / 32 / pData->divFre / pData->curRealFre * 10 - 1;
//        LOG_DEBUG("index %d current frequency %.1f, divFre %d, error %.4f%%", i++, pData->curRealFre / 10.0, pData->divFre, error * 100);

//        pData->fpgaResult.fre = pData->curRealFre;
//        dds_waveSeting(pData->curRealFre / 10.0, 0, SIN_WAVE, 0);
//        fpga_writeDivFre(pData->divFre);

//        data_setIsIgnore(L_TRUE);
//        for (j = 0; j < ignoreNum; ++j)
//        {
//            fpga_start();
//            data_resetRecieved();
//            timer_start(TIMER_FPGA_TIMEOUT, 3000, NULL);
//            while (data_getRecieved() < 2)
//            {
//                if(L_FALSE == timer_isTimerStart(TIMER_FPGA_TIMEOUT))
//                {
//                    LOG_DEBUG("fpga disconnect!!");
//                    led_end();
//                    return F_FAILED;
//                }
//                osDelay(1);
//            }
//            fpga_end();
//        }

//        data_setIsIgnore(L_FALSE);
//        pData->fpgaResult.R.real = 0;
//        pData->fpgaResult.R.imagin = 0;
//        for (j = 0; j < averageNum; ++j)
//        {
//            fpga_start();
//            data_resetRecieved();
//            timer_start(TIMER_FPGA_TIMEOUT, 3000, NULL);
//            while (data_getRecieved() < 2)
//            {
//                if(L_FALSE == timer_isTimerStart(TIMER_FPGA_TIMEOUT))
//                {
//                    LOG_DEBUG("fpga disconnect!!");
//                    led_end();
//                    return F_FAILED;
//                }
//                osDelay(1);
//            }
//            fpga_end();
//            get_RValue(pData->fpgaResult, &result);
//            pData->fpgaResult.R.real += result.real / averageNum;
//            pData->fpgaResult.R.imagin += result.imagin / averageNum;
//        }

//        flash_write(pSetting->blockAddress[index] + pSetting->blockSize[index], &(pData->fpgaResult), sizeof(FPGA_RESULT));
//        pSetting->blockSize[index] += sizeof(FPGA_RESULT);

//        uart_wifi_sendResult(pData->fpgaResult);
//    }

//    led_end();
//    data_setIsStart(L_FALSE);
//    uart_wifi_sendEnd();
//    LOG_DEBUG("measure interrupt");

    return F_SUCCESS;
}

static int modem_measureSuccess(const TASK_MSG *msg)
{
//    SETTING *pSetting = NULL;

//    pSetting = data_getSetting();
//    LOG_DEBUG("measure success");
//    pSetting->currentIndex++;
//    pSetting->haveMeasuredNum++;
//    data_initData();
//    if (pSetting->currentIndex > BLOCK_NUM - 1)
//    {
//        pSetting->currentIndex = 1;
//    }
//    if (pSetting->haveMeasuredNum > BLOCK_NUM - 1)
//    {
//        pSetting->haveMeasuredNum = BLOCK_NUM - 1;
//    }
//    data_saveSetting();
//    uart_wifi_sendEnd();
//    led_end();
    return F_SUCCESS;
}

static int modem_measureOnce(const TASK_MSG *msg)
{
//    DATA *pData = NULL;
//    float error = 0;
//    int j = 0;
//    Complex result = {0};
//    u8 averageNum = 0;
//    u8 ignoreNum = 0;

//    pData = data_getData();
//    averageNum = data_getAverageNum();
//    ignoreNum = data_getIgnoreNum();

//    dds_waveSeting(10, 0, SIN_WAVE, 0);

//    led_start();

//    timer_start(TIMER_DELAY, 3000, NULL);
//    while(L_TRUE == timer_isTimerStart(TIMER_DELAY))
//    {
//        osDelay(100);
//    }

//    LOG_DEBUG("start measure");

//    if(F_SUCCESS != get_fre(1))
//    {
//        fpga_end();
//        LOG_ERROR("get frequency error");
//        return F_FAILED;
//    }

//    error = FPGA_SYSTEM_TICK / 32 / pData->divFre / pData->curRealFre * 10 - 1;
//    LOG_DEBUG("current frequency %.1f, divFre %d, error %.4f%%", pData->curRealFre / 10.0, pData->divFre, error * 100);

//    pData->fpgaResult.fre = pData->curRealFre;
//    dds_waveSeting(pData->curRealFre / 10.0, 0, SIN_WAVE, 0);
//    fpga_writeDivFre(pData->divFre);

//    data_setIsIgnore(L_TRUE);
//    for (j = 0; j < ignoreNum; ++j)
//    {
//        fpga_start();
//        data_resetRecieved();
//        timer_start(TIMER_FPGA_TIMEOUT, 3000, NULL);
//        while (data_getRecieved() < 2)
//        {
//            if(L_FALSE == timer_isTimerStart(TIMER_FPGA_TIMEOUT))
//            {
//                LOG_DEBUG("fpga disconnect!!");
//                led_end();
//                return F_FAILED;
//            }
//            osDelay(1);
//        }
//        fpga_end();
//    }

//    data_setIsIgnore(L_FALSE);
//    pData->fpgaResult.R.real = 0;
//    pData->fpgaResult.R.imagin = 0;
//    for (j = 0; j < averageNum; ++j)
//    {
//        fpga_start();
//        data_resetRecieved();
//        timer_start(TIMER_FPGA_TIMEOUT, 3000, NULL);
//        while (data_getRecieved() < 2)
//        {
//            if(L_FALSE == timer_isTimerStart(TIMER_FPGA_TIMEOUT))
//            {
//                LOG_DEBUG("fpga disconnect!!");
//                led_end();
//                return F_FAILED;
//            }
//            osDelay(1);
//        }
//        fpga_end();
//        get_RValue(pData->fpgaResult, &result);
//        pData->fpgaResult.R.real += result.real / averageNum;
//        pData->fpgaResult.R.imagin += result.imagin / averageNum;
//    }

//    showResult(pData->fpgaResult);

//    led_end();

//    dds_waveSeting(0, 0, SIN_WAVE, 0);
//    // LOG_DEBUG("measure interrupt");

    return F_SUCCESS;
}

static int modem_getMeasureData(const TASK_MSG *msg)
{
//    SETTING *pSetting = NULL;
//    SETTING sendSetting = {0};
//    DATA *pData = NULL;
//    int i = 0;

//    pSetting = data_getSetting();
//    pData = data_getData();

//    if(pData->getIndex == 0)
//    {
//        LOG_ERROR("there has been no messure exceed");
//        return F_FAILED;
//    }

//    if (0 == pSetting->blockSize[pData->getIndex])
//    {
//        LOG_DEBUG("no data here");
//        return F_FAILED;
//    }

//    if(F_SUCCESS == flash_read(pSetting->blockAddress[pData->getIndex], &sendSetting, sizeof(SETTING)))
//    {
//        if (sendSetting.flag != SETTING_FLAG)
//        {
//            LOG_DEBUG("read setting failed");
//            return F_FAILED;
//        }
//        uart_wifi_sendSetting(&sendSetting);
//    }

//    data_setIsStart(L_TRUE);
//    led_start();
//    LOG_DEBUG("get measure data, index: %d", pData->getIndex);
//    for(i = 0; L_TRUE == data_isStart(); i++)
//    {
//        if(F_SUCCESS == flash_read(pSetting->blockAddress[pData->getIndex] + i * sizeof(FPGA_RESULT) + sizeof(SETTING), &(pData->fpgaResult), sizeof(FPGA_RESULT)))
//        {
//            uart_wifi_sendResult(pData->fpgaResult);
//            LOG_DEBUG("index %d", i + 1);
//            showResult(pData->fpgaResult);
//            if ((i + 1) * sizeof(FPGA_RESULT) >= pSetting->blockSize[pData->getIndex] - sizeof(SETTING))
//            {
//                LOG_DEBUG("read data success");
//                break;
//            }
//        }
//        else
//        {
//            LOG_ERROR("flash read error");
//            break;
//        }
//    }

//    uart_wifi_sendEnd();
//    led_end();
//    data_initData();
    return F_SUCCESS;
}

static TASK_MSG_MAP modem_msgMap[] =
{
    {MEASURE_START,             modem_measureStart},
    {MEASURE_SUCCESS,           modem_measureSuccess},
    {MEASURE_ONCE,              modem_measureOnce},
    {GET_MEASURE_DATA,          modem_getMeasureData},
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

