#ifndef DSP_FILTER
#define DSP_FILTER

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "arm_math.h"
#include "log.h"

#define SINWAVE_SAMPLE 512
#define SAMPLE_NUM 256
#define BLOCK_SIZE 32
#define ADC_CHANEL 3
#define ORDER 2

//#define 
int dsp_print2(float32_t *data1, float32_t *data2);
int dsp_print(float32_t *data);//float32_t *data
int dsp_test(void);
int dsp_init(void);
float32_t dsp_iir_2_cal_unit(float32_t data);
int dsp_multi_frequency(void);
int dsp_ave(uint16_t * buffer);
int dsp_filt(float32_t *data);
int dsp_raising_detect(float *signal);

#define FS 10000
#define F0  200
//#define point_per_period 50

#endif


