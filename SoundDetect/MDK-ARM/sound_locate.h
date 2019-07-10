#ifndef SOUND
#define SOUND

#include <stdio.h>
#include "cmsis_os.h"
#include <math.h>

#define X 1000.0f
#define Y 1000.0f
#define SOUND_V 340.0f

typedef struct{
	float x;
	float y;
}Point;
int locatePoint(Point *calPoint,float d1,float d2);




#endif