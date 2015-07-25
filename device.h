#ifndef __SLDEVICE_MANAGER_
#define __SLDEVICE_MANAGER_
#include "slconfig.h"

typedef void (*device_setup)();
typedef void (*exec_func)(int,char (*)[MAX_ARGUMENT_LENGTH]);
typedef void (*other_init)();

struct device {
	char cmd[32];
	device_setup s_func;
	exec_func    e_func;
};

class DeviceManager {
public:
	DeviceManager(){}
	virtual ~DeviceManager(){}
public:
	static device devs[];
	static other_init o_init[];
	static device* findDevice(const char*);
	static void  device_all_setup();
};	
#endif

