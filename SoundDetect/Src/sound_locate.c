#include "sound_locate.h"

Point dick = {0.0f,0.0f};

int locatePoint(Point *calPoint,float t1,float t2){
	float a,b,c,r;
	float d1_temp,d2_temp;
	float d1,d2;
	
	d1 = SOUND_V*t1;
	d2 = SOUND_V*t2;
	d1_temp = X*X - d1*d1;
	d2_temp = Y*Y - d2*d2;
	
	a = d1_temp + d2*d2;
	b = d1*d1_temp + d2*d2_temp;
	c = d1_temp*d1_temp + d2_temp*d2_temp;
	
	r = (-b-sqrt(b*b-4*a*c))/2*a;
	
	calPoint->x = (d1_temp+2*r*d1)*(d1_temp+2*r*d1)/2;
	calPoint->y = (d2_temp+2*r*d2)*(d2_temp+2*r*d2)/2;
	
	return 0;
}