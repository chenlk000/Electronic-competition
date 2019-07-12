#include "triangleDriver.h"
#include "log.h"
arm_matrix_instance_f32 V_global;

float ref_v_abc[3];
float ref_v_basic[3];
float ref_trans_basic_abc[3*3];
float ref_trans_global_basic[3*3];

int v3_init(TriangleDriver* Tri){
	
	arm_mat_init_f32(&Tri->V_abc,3,1,ref_v_abc);
	arm_mat_init_f32(&Tri->V_basic,3,1,ref_v_basic);
	arm_mat_init_f32(&Tri->Trans_basic_abc,3,3,ref_trans_basic_abc);
	arm_mat_init_f32(&Tri->Trans_global_basic,3,3,ref_trans_global_basic);
	
	Tri->vx = Tri->V_basic.pData;
	Tri->vy = Tri->V_basic.pData+1;
	Tri->omiga = Tri->V_basic.pData+2;
	
	Tri->v_back  = Tri->V_abc.pData;
	Tri->v_left  = Tri->V_abc.pData+1;
	Tri->v_right = Tri->V_abc.pData+2;
	return F_SUCCESS;
}

void update_trans_basic_abc(TriangleDriver* Tri){
	
	Tri->Trans_basic_abc.pData[0] = 1;
	Tri->Trans_basic_abc.pData[1] = -cos(Tri->phi);
	Tri->Trans_basic_abc.pData[2] = -cos(Tri->phi);
	Tri->Trans_basic_abc.pData[3] = 0;
	Tri->Trans_basic_abc.pData[4] = -sin(Tri->phi);
	Tri->Trans_basic_abc.pData[5] = sin(Tri->phi);
	Tri->Trans_basic_abc.pData[6] = L;
	Tri->Trans_basic_abc.pData[7] = L;
	Tri->Trans_basic_abc.pData[8] = L;

}
void update_trans_global_basic(TriangleDriver* Tri){
	Tri->Trans_global_basic.pData[0] = cos(Tri->theta);
	Tri->Trans_global_basic.pData[1] = sin(Tri->theta);
	Tri->Trans_global_basic.pData[2] = 0;
	Tri->Trans_global_basic.pData[3] = -sin(Tri->theta);
	Tri->Trans_global_basic.pData[4] =	cos(Tri->theta);
	Tri->Trans_global_basic.pData[5] = 0;
	Tri->Trans_global_basic.pData[6] = 0;
	Tri->Trans_global_basic.pData[7] = 0;
	Tri->Trans_global_basic.pData[8] = 1;
}
int v3_calculate(TriangleDriver* Tri){
	
		arm_status status;
		
		status = arm_mat_mult_f32(&Tri->V_basic, &Tri->Trans_global_basic, &Tri->Trans_basic_abc);	
		if(status){	
			LOG_PRINT("Trans from global to basic failed, state = %d",status);	
			return F_FAILED;
		}
			status = arm_mat_mult_f32(&Tri->V_basic, &Tri->Trans_basic_abc, &Tri->V_abc);
		if(status){	
			LOG_PRINT("Trans from basic to abc failed, state = %d",status);	
			return F_FAILED;
		}
		
		print_matrix_f32(&Tri->V_abc);
		
		LOG_PRINT("status = %d",status);	
    LOG_PRINT("multiple ok");
    return F_SUCCESS;
		
}






