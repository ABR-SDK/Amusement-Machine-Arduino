#ifndef __SLMISC_
#define __SLMISC_
#include "slconfig.h"
inline int parse_int_dec(const char* p) {
	bool isNeg = false;
	int ret = 0;
	if(*p == '-') {
		isNeg = true;
		p++;
	}
	
	while(*p) {
		if(*p < '0' || *p > '9') {
			ret = 0;
			break;
		}
		ret *= 10;
		ret += *p - '0';
		p++;
	}
	return ret;
}

void mpu9150_setup();
void ms5803_setup();

void motor_init();
void motor_go(int args,char (*argv)[MAX_ARGUMENT_LENGTH]);

void esc_init();
void esc_switch(int args,char (*argv)[MAX_ARGUMENT_LENGTH]);

#endif

