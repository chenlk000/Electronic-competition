#include "dsp_filter.h"
#define SAMPLE_NUM 1024
#define BLOCK_SIZE 32
#define ADC_CHANEL 3
#define ORDER 10
volatile short adc_buffer[ADC_CHANEL*SAMPLE_NUM] = {0};
volatile float32_t adc_ave0_buf0[SAMPLE_NUM];
volatile float32_t adc_ave0_buf1[SAMPLE_NUM];
volatile float32_t adc_ave0_buf2[SAMPLE_NUM];

volatile float32_t adc_out_buf0[SAMPLE_NUM];
volatile float32_t adc_out_buf1[SAMPLE_NUM];
volatile float32_t adc_out_buf2[SAMPLE_NUM];
	
volatile uint16_t adc_ch0[SAMPLE_NUM] = {0};
volatile uint16_t adc_ch1[SAMPLE_NUM] = {0};
volatile uint16_t adc_ch2[SAMPLE_NUM] = {0};

int adc_ave[ADC_CHANEL] = {0};

float32_t numerator[ORDER+1] = { 0.250255f, 0.000101f,-0.000097f, 0.000097f,-0.000096f, 0.000096f,-0.000096, 0.000097f,-0.000098f, 0.0001018f, 0.2502557f};// {0.250029f,0.000039f,-0.000038f,0.000039f,0.250029f};
float32_t first_state[SAMPLE_NUM+ORDER-1] = {0};

int dsp_test(void){
	int i;
	
	dsp_ave(adc_buffer);
	for(i=0;i<SAMPLE_NUM;i++){
			adc_ave0_buf0[i] = (float)(adc_buffer[i*3] - adc_ave[0]);
			adc_ave0_buf1[i] = (float)(adc_buffer[i*3+1] - adc_ave[1]);			
			adc_ave0_buf2[i] = (float)(adc_buffer[i*3+2] - adc_ave[2]);
		}
		dsp_print(adc_ave0_buf0);
		
		for(i=0;i<SAMPLE_NUM;i++){
		adc_ave0_buf0[i] *= sin_wave_12ADC [(i%10)*SINWAVE_SAMPLE/10];
		adc_ave0_buf1[i] *= sin_wave_12ADC [(i%10)*SINWAVE_SAMPLE/10];
		adc_ave0_buf2[i] *= sin_wave_12ADC [(i%10)*SINWAVE_SAMPLE/10];
	}
		
		
//	dsp_print(adc_ave0_buf0);	
//	log_print2("before");
//	dsp_print(adc_ave0_buf0);
//	dsp_filt();
//	log_print2("after");
//	dsp_print(adc_out_buf0);
		
//		LOG_DEBUG("adc_ave0 = %d",adc_ave[0]);
//		LOG_DEBUG("adc_ave1 = %d",adc_ave[1]);
//		LOG_DEBUG("adc_ave2 = %d",adc_ave[2]);
}

int dsp_init(void){ 
	
	
}


int dsp_print(float32_t *data){//
	int i;
	for(i=0;i<SAMPLE_NUM;i++){
		log_print2("%f\n", (float)(data[i]));
}
		//	log_print2("\r\n\r\n");
}

int dsp_print2(float32_t *data1,float32_t *data2){//
	int i;
		for(i=0;i<SAMPLE_NUM;i++){
		log_print2("%f,", (float)(data1[i]));
		log_print2("%f\n", (float)(data2[i]));
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
			adc_ave0_buf0[i] *= sin_wave_12ADC [(i%5)*SINWAVE_SAMPLE/5];
			adc_ave0_buf1[i] *= sin_wave_12ADC [(i%5)*SINWAVE_SAMPLE/5];
			adc_ave0_buf2[i] *= sin_wave_12ADC [(i%5)*SINWAVE_SAMPLE/5];
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

int dsp_filt(){
	int i,j;
	char state;
	uint32_t numBlocks = SAMPLE_NUM/BLOCK_SIZE;
	
	arm_fir_instance_f32 filter0_inst;
	arm_fir_init_f32(&filter0_inst, ORDER+1, numerator, first_state, BLOCK_SIZE);
	
	for(i=0;i<numBlocks;i++){
		arm_fir_f32(&filter0_inst, adc_ave0_buf0 + (i * BLOCK_SIZE), adc_out_buf0 + (i * BLOCK_SIZE), BLOCK_SIZE);
//		if(!state)
//			DEBUG_PRINT("State is %d",state);
//		arm_fir_f32(&filter0_inst, adc_ave0_buf1 + (i * BLOCK_SIZE), adc_out_buf1 + (i * BLOCK_SIZE), BLOCK_SIZE);			
//		arm_fir_f32(&filter0_inst, adc_ave0_buf2 + (i * BLOCK_SIZE), adc_out_buf2 + (i * BLOCK_SIZE), BLOCK_SIZE);	
	}
}
