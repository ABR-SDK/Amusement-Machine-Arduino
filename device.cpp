#include <Arduino.h>
#include "device.h"
#include "timer.h"
#include "misc.h"


void example_init() {
	Serial.println("log(\"example init\")");
}

void example_exec(int args,char (*argv)[MAX_ARGUMENT_LENGTH]) {
	SLSERIAL.println("example trigger");
	SLSERIAL.print(F("log(\"argument count:"));
	SLSERIAL.print(args);
	SLSERIAL.println(F("\")"));
	
	for(int i = 0 ; i < args;i++) {
		SLSERIAL.print(F("log(\"argument "));
		SLSERIAL.print(i);
		SLSERIAL.print(":");
		SLSERIAL.print(&argv[i][0]);
		SLSERIAL.println(F("\")"));
	}
}


/********************************************
 *
 ********************************************/
device DeviceManager::devs[] = {
	{"esc_switch",esc_init,esc_switch},
	{"go",motor_init,motor_go},
	{"",0,0},
};

/********************************************
 *
 ********************************************/
other_init DeviceManager::o_init[]= {
	mpu9150_setup,ms5803_setup,
	0,
};

device* DeviceManager::findDevice(const char* p) {
	int device_nums = sizeof(devs)/sizeof(device) - 1;
	device* dev = NULL;
	
	for(int i = 0; i < device_nums;i++) {
		if(!strcmp(p,devs[i].cmd)) {
			dev = &devs[i];
			break;
		}
	}

	return dev;
}

void  DeviceManager::device_all_setup() {
	int device_nums = sizeof(devs)/sizeof(device) - 1;
	
	for(int i = 0;i < device_nums;i++) {
		if(devs[i].s_func)
			devs[i].s_func();
	}
	
	device_nums = sizeof(o_init)/sizeof(other_init) - 1;
	for(int i = 0;i < device_nums;i++) {
		if(o_init[i])
			(*o_init[i])();
	}
}

