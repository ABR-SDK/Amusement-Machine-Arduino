#include <arduino.h>
#include "misc.h"
#include "slservo.h"
#include "slconfig.h"

#define CAMERA_MOUNT_PIN 11
Servo _camera;

void camera_mount_init() {
	
	_camera.attach(CAMERA_MOUNT_PIN);
	delay(10);	
	_camera.writeMicroseconds(1500);
	
}

void camera_title(int args,char (*argv)[MAX_ARGUMENT_LENGTH]) {
	int _title = 0;
	
	_title = parse_int_dec(argv[0]);
	
	if(_title < 1000 || _title > 2000)_title = 1500;
	
	_camera.writeMicroseconds(_title);
}