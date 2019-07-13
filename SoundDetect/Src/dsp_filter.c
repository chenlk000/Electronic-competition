#include "dsp_filter.h"
#include "cmsis_os.h"
#include "main.h"
#include "msg.h"
#include <math.h>

const short sin_wave_12ADC[SINWAVE_SAMPLE] = {
25,
50,
75,
100 ,
126 ,
151 ,
176 ,
201 ,
226 ,
251 ,
276 ,
301 ,
325 ,
350 ,
375 ,
400 ,
424 ,
449 ,
473 ,
498 ,
522 ,
546 ,
570 ,
595 ,
619 ,
642 ,
666 ,
690 ,
714 ,
737 ,
760 ,
784 ,
807 ,
830 ,
853 ,
876 ,
898 ,
921 ,
943 ,
965 ,
988 ,
1009,
1031,
1053,
1074,
1096,
1117,
1138,
1159,
1179,
1200,
1220,
1240,
1260,
1280,
1299,
1319,
1338,
1357,
1375,
1394,
1412,
1430,
1448,
1466,
1483,
1500,
1517,
1534,
1551,
1567,
1583,
1599,
1615,
1630,
1645,
1660,
1674,
1689,
1703,
1717,
1730,
1744,
1757,
1769,
1782,
1794,
1806,
1818,
1829,
1840,
1851,
1862,
1872,
1882,
1892,
1902,
1911,
1920,
1928,
1937,
1945,
1952,
1960,
1967,
1974,
1980,
1987,
1993,
1998,
2004,
2009,
2013,
2018,
2022,
2026,
2029,
2033,
2036,
2038,
2040,
2042,
2044,
2046,
2047,
2047,
2048,
2048,
2048,
2047,
2047,
2046,
2044,
2042,
2040,
2038,
2036,
2033,
2029,
2026,
2022,
2018,
2013,
2009,
2004,
1998,
1993,
1987,
1980,
1974,
1967,
1960,
1952,
1945,
1937,
1928,
1920,
1911,
1902,
1892,
1882,
1872,
1862,
1851,
1840,
1829,
1818,
1806,
1794,
1782,
1769,
1757,
1744,
1730,
1717,
1703,
1689,
1674,
1660,
1645,
1630,
1615,
1599,
1583,
1567,
1551,
1534,
1517,
1500,
1483,
1466,
1448,
1430,
1412,
1394,
1375,
1357,
1338,
1319,
1299,
1280,
1260,
1240,
1220,
1200,
1179,
1159,
1138,
1117,
1096,
1074,
1053,
1031,
1009,
988 ,
965 ,
943 ,
921 ,
898 ,
876 ,
853 ,
830 ,
807 ,
784 ,
760 ,
737 ,
714 ,
690 ,
666 ,
642 ,
619 ,
595 ,
570 ,
546 ,
522 ,
498 ,
473 ,
449 ,
424 ,
400 ,
375 ,
350 ,
325 ,
301 ,
276 ,
251 ,
226 ,
201 ,
176 ,
151 ,
126 ,
100 ,
75  ,
50  ,
25  ,
0   ,
-25 ,
-50 ,
-75 ,
-100,
-126,
-151,
-176,
-201,
-226,
-251,
-276,
-301,
-325,
-350,
-375,
-400,
-424,
-449,
-473,
-498,
-522,
-546,
-570,
-595,
-619,
-642,
-666,
-690,
-714,
-737,
-760,
-784,
-807,
-830,
-853,
-876,
-898,
-921,
-943,
-965,
-988,
-1009,
-1031,
-1053,
-1074,
-1096,
-1117,
-1138,
-1159,
-1179,
-1200,
-1220,
-1240,
-1260,
-1280,
-1299,
-1319,
-1338,
-1357,
-1375,
-1394,
-1412,
-1430,
-1448,
-1466,
-1483,
-1500,
-1517,
-1534,
-1551,
-1567,
-1583,
-1599,
-1615,
-1630,
-1645,
-1660,
-1674,
-1689,
-1703,
-1717,
-1730,
-1744,
-1757,
-1769,
-1782,
-1794,
-1806,
-1818,
-1829,
-1840,
-1851,
-1862,
-1872,
-1882,
-1892,
-1902,
-1911,
-1920,
-1928,
-1937,
-1945,
-1952,
-1960,
-1967,
-1974,
-1980,
-1987,
-1993,
-1998,
-2004,
-2009,
-2013,
-2018,
-2022,
-2026,
-2029,
-2033,
-2036,
-2038,
-2040,
-2042,
-2044,
-2046,
-2047,
-2047,
-2048,
-2048,
-2048,
-2047,
-2047,
-2046,
-2044,
-2042,
-2040,
-2038,
-2036,
-2033,
-2029,
-2026,
-2022,
-2018,
-2013,
-2009,
-2004,
-1998,
-1993,
-1987,
-1980,
-1974,
-1967,
-1960,
-1952,
-1945,
-1937,
-1928,
-1920,
-1911,
-1902,
-1892,
-1882,
-1872,
-1862,
-1851,
-1840,
-1829,
-1818,
-1806,
-1794,
-1782,
-1769,
-1757,
-1744,
-1730,
-1717,
-1703,
-1689,
-1674,
-1660,
-1645,
-1630,
-1615,
-1599,
-1583,
-1567,
-1551,
-1534,
-1517,
-1500,
-1483,
-1466,
-1448,
-1430,
-1412,
-1394,
-1375,
-1357,
-1338,
-1319,
-1299,
-1280,
-1260,
-1240,
-1220,
-1200,
-1179,
-1159,
-1138,
-1117,
-1096,
-1074,
-1053,
-1031,
-1009,
-988,
-965,
-943,
-921,
-898,
-876,
-853,
-830,
-807,
-784,
-760,
-737,
-714,
-690,
-666,
-642,
-619,
-595,
-570,
-546,
-522,
-498,
-473,
-449,
-424,
-400,
-375,
-350,
-325,
-301,
-276,
-251,
-226,
-201,
-176,
-151,
-126,
-100,
-75 ,
-50 ,
-25 ,
0   
};

volatile short adc_buffer[ADC_CHANEL*SAMPLE_NUM] = {0};
volatile float32_t adc_ave0_buf0[SAMPLE_NUM];
volatile float32_t adc_ave0_buf1[SAMPLE_NUM];
volatile float32_t adc_ave0_buf2[SAMPLE_NUM];

volatile float32_t adc_mult_buf0[SAMPLE_NUM];
volatile float32_t adc_mult_buf1[SAMPLE_NUM];
volatile float32_t adc_mult_buf2[SAMPLE_NUM];

volatile float32_t adc_out_buf0[SAMPLE_NUM];
volatile float32_t adc_out_buf1[SAMPLE_NUM];
volatile float32_t adc_out_buf2[SAMPLE_NUM]; 
	
volatile uint16_t adc_ch0[SAMPLE_NUM] = {0};
volatile uint16_t adc_ch1[SAMPLE_NUM] = {0};
volatile uint16_t adc_ch2[SAMPLE_NUM] = {0};
extern TIM_HandleTypeDef htim8;

int adc_ave[ADC_CHANEL] = {0};

//float32_t numerator[ORDER+1] = { 0.250255f, 0.0001018f,-0.000098f, 0.000097f,-0.000096f, 0.000096f,-0.000096, 0.000097f,-0.000098f, 0.0001018f, 0.250255f};// {0.250029f,0.000039f,-0.000038f,0.000039f,0.250029f};
//float32_t numerator[ORDER+1] = { 0.2500293f, 0.0000394f, -0.0000390f, 0.0000394f, 0.2500293f};

short point_per_period = 20;

float32_t first_state[SAMPLE_NUM+ORDER-1] = {0};
const float32_t IIR_n1 =  2.000000f, IIR_n2 = 1.000000f;
const float32_t IIR_d1 = -1.955578f, IIR_d2 =  0.9565436f;
const float32_t IIR_g = 0.0002413f;

const float32_t therehold_down = 50000; 
const float32_t therehold_up = 450000; 


int dsp_raising_detect(float *signal){
	short i,cnt = 0;	
	char state = 0;
	int signal_int = 0;
//	char data[2];
	for(i=0;i<SAMPLE_NUM;i++){
		signal_int = abs((int)(signal[i]));
		if((state == 0 )&&( signal_int<therehold_up))
			state = 1;
		else if((state == 1)&&  (signal_int>therehold_up)){
				cnt++;
					if(cnt==5)
						return i;
		}
		else{
			state = 0;
			cnt = 0;
		}		
	}
	return 0;
}

int dsp_test(void){
	int i;
	short label[3] = {0};
	unsigned int cnt = 0;
	dsp_ave(adc_buffer);
	for(i=0;i<SAMPLE_NUM;i++){
		adc_ave0_buf0[i] = (float)(adc_buffer[i*3] - adc_ave[0]);
		adc_ave0_buf1[i] = (float)(adc_buffer[i*3+1] - adc_ave[1]);			
		adc_ave0_buf2[i] = (float)(adc_buffer[i*3+2] - adc_ave[2]);
	}
	
		htim8.Instance->CR1 |= 1<<0; //start trans
		
//		dsp_print(adc_ave0_buf0);	
//	
		
		for(i=0;i<SAMPLE_NUM;i++){
			adc_mult_buf0[i] = adc_ave0_buf0[i] * sin_wave_12ADC [(short)((i%point_per_period)*(float)SINWAVE_SAMPLE/point_per_period)];
			adc_mult_buf1[i] = adc_ave0_buf1[i] * sin_wave_12ADC [(short)((i%point_per_period)*(float)SINWAVE_SAMPLE/point_per_period)];
			adc_mult_buf2[i] = adc_ave0_buf2[i] * sin_wave_12ADC [(short)((i%point_per_period)*(float)SINWAVE_SAMPLE/point_per_period)];
		}

		dsp_filt(adc_mult_buf0);
		dsp_print2(adc_mult_buf0,adc_out_buf0);
			
		label[0] = dsp_raising_detect(adc_out_buf0 );
		label[1] = dsp_raising_detect(adc_out_buf1 );
		label[2] = dsp_raising_detect(adc_out_buf2 );
	
		if(label[0]||label[1]){//||label[2]
			if(cnt<100)
				cnt++;
			else{
				log_print("time out!");
				cnt=0;
			}
			if(label[0]&&label[1]){//&&label[2]
				LOG_DEBUG("label[0] = %d,label[1] = %d,cnt = %d"); //t12 = %f,
				label[0] = 0;
				label[1] = 0;
			}
		}
		
		
//	dsp_print(adc_ave0_buf0);	
//	log_print2("before");
//	dsp_print(adc_ave0_buf0);
//	
//	log_print2("after");
//	dsp_print(adc_out_buf0);
		
//		LOG_DEBUG("adc_ave0 = %d",adc_ave[0]);
//		LOG_DEBUG("adc_ave1 = %d",adc_ave[1]);
//		LOG_DEBUG("adc_ave2 = %d",adc_ave[2]);
}


float32_t dsp_iir_2_cal_unit(float32_t data){
	
	static float32_t z0 = 0.f, z1 = 0.f;
	float32_t rtn;
	rtn = z0 + data;
	z0 = z1 + (data *IIR_n1) - (rtn * IIR_d1);
	z1 = (data * IIR_n2) - (rtn * IIR_d2);
	return rtn * IIR_g;
}


int dsp_print(float32_t *data){//
	int i;
	for(i=0;i<SAMPLE_NUM;i++){
			log_print2("%f,",(float)(sin_wave_12ADC[(short)((i%point_per_period)*(float)SINWAVE_SAMPLE/point_per_period)]));
			log_print("%d,%f",i%point_per_period,(float)SINWAVE_SAMPLE/point_per_period);
//			log_print2("%f,", adc_mult_buf0[i]);
			log_print2("%f\n", (float)(data[i]));
		}
}

int dsp_print2(float32_t *data1,float32_t *data2){//
	int i;
		for(i=0;i<SAMPLE_NUM;i++){
			log_print2("%f,", data1[i]);
			log_print2("%f\n", data2[i]);
	}
}


int dsp_multi_frequency(void){
		short i;
	
		for(i=0;i<SAMPLE_NUM;i++){
			adc_ave0_buf0[i] = (float)(adc_buffer[i*3] - adc_ave[0]);
			adc_ave0_buf1[i] = (float)(adc_buffer[i*3+1] - adc_ave[1]);			
			adc_ave0_buf2[i] = (float)(adc_buffer[i*3+2] - adc_ave[2]);
		}
		
		for(i=0;i<SAMPLE_NUM;i++){
			adc_ave0_buf0[i] *= sin_wave_12ADC [(i%point_per_period)*SINWAVE_SAMPLE/point_per_period];
			adc_ave0_buf1[i] *= sin_wave_12ADC [(i%point_per_period)*SINWAVE_SAMPLE/point_per_period];
			adc_ave0_buf2[i] *= sin_wave_12ADC [(i%point_per_period)*SINWAVE_SAMPLE/point_per_period];
		}
		
}

int dsp_ave(uint16_t * buffer){
	int i;
	volatile uint32_t adc_add[ADC_CHANEL] = {0}; 
	adc_ave[0] = 0;
	adc_ave[1] = 0;
	adc_ave[2] = 0;
	for(i=0;i<SAMPLE_NUM;i++){
			adc_add[0] += adc_buffer[i*3];
			adc_add[1] += adc_buffer[i*3+1];
			adc_add[2] += adc_buffer[i*3+2];
	}
	
	adc_ave[0] = adc_add[0] / SAMPLE_NUM;
	adc_ave[1] = adc_add[1] / SAMPLE_NUM;
	adc_ave[2] = adc_add[2] / SAMPLE_NUM;
}


int dsp_filt(float32_t *data){
	int i;
//	char state;
	for(i = 0;i<SAMPLE_NUM;i++)
		adc_out_buf0[i] =  dsp_iir_2_cal_unit(*(data+i));
	
	
//	uint32_t numBlocks = SAMPLE_NUM/BLOCK_SIZE;
//	
//	arm_fir_instance_f32 filter0_inst;
//	arm_fir_init_f32(&filter0_inst, ORDER+1, numerator, first_state, BLOCK_SIZE);
//	
//	for(i=0;i<numBlocks;i++){
//		arm_fir_f32(&filter0_inst, adc_ave0_buf0 + (i * BLOCK_SIZE), adc_out_buf0 + (i * BLOCK_SIZE), BLOCK_SIZE);
////		if(!state)
////			DEBUG_PRINT("State is %d",state);
////		arm_fir_f32(&filter0_inst, adc_ave0_buf1 + (i * BLOCK_SIZE), adc_out_buf1 + (i * BLOCK_SIZE), BLOCK_SIZE);			
////		arm_fir_f32(&filter0_inst, adc_ave0_buf2 + (i * BLOCK_SIZE), adc_out_buf2 + (i * BLOCK_SIZE), BLOCK_SIZE);	
//	}
}
