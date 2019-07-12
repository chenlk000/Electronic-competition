#ifndef TRIDRIVE
#define TRIDRIVE
// F5 5F 08 01 01 00 F5 OFF GYRO SINGLE RING
// F5 5F 08 01 01 02 F3 

#include "stdint.h"
#include "arm_math.h"
#include "types.h"

#define L 100


typedef struct {
	float * v_left;
	float * v_right;
	float * v_back;
	
	float phi;
	float theta;
	
	float * omiga; //angle speed
	float * vx; //left speed
	float * vy; //front speed
	
	arm_matrix_instance_f32 V_abc;
	arm_matrix_instance_f32 V_basic;
	arm_matrix_instance_f32 Trans_basic_abc;
	arm_matrix_instance_f32 Trans_global_basic;
	
}TriangleDriver;


int v3_calculate(TriangleDriver* Tri);

#endif
