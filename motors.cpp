#include <arduino.h>
#include "misc.h"
#include "slservo.h"
#include "slconfig.h"

#define PORT_PIN 6
#define STARBOARD_PIN 7
#define VERTICAL_LEFT_PIN 8
#define VERTICAL_RIGHT_PIN 9

#define MIDPOINT 1500

Servo port;
Servo starboard;
Servo vertical_left;
Servo vertical_right;

void motor_init() {
	
	port.attach(PORT_PIN);
	starboard.attach(STARBOARD_PIN);
	vertical_left.attach(VERTICAL_LEFT_PIN);
	vertical_right.attach(VERTICAL_RIGHT_PIN);
	
	delay(10);
	port.writeMicroseconds(1500);
	starboard.writeMicroseconds(1500);
	vertical_left.writeMicroseconds(1500);
	vertical_right.writeMicroseconds(1500);
	
}

void motor_go(int args,char (*argv)[MAX_ARGUMENT_LENGTH]) {
	int p_s,s_s,vl_s,vr_s;
	if(args != 3) {
		return;
	}
	
	p_s = parse_int_dec(argv[0]);
	s_s = parse_int_dec(argv[1]);
	vl_s = parse_int_dec(argv[2]);
	vr_s = parse_int_dec(argv[3]);
/*
	SLSERIAL.print("log1(");
  SLSERIAL.print(p_s);
  SLSERIAL.print(",");
  SLSERIAL.print(s_s);
  SLSERIAL.print(",");
  SLSERIAL.print(v_s);
  SLSERIAL.println(")");
*/	
	if(p_s < 1000 || p_s > 2000)p_s = 1500;
	if(s_s < 1000 || s_s > 2000)s_s = 1500;
	if(vl_s < 1000 || vl_s > 2000)vl_s = 1500;
	if(vr_s < 1000 || vr_s > 2000)vr_s = 1500;
	
	SLSERIAL.print("log(\"motors(");
	SLSERIAL.print(p_s);
	SLSERIAL.print(",");
	SLSERIAL.print(s_s);
	SLSERIAL.print(",");
	SLSERIAL.print(vl_s);
	SLSERIAL.print(",");
	SLSERIAL.print(vr_s);
	SLSERIAL.println(")\")");
	port.writeMicroseconds(p_s);
	starboard.writeMicroseconds(s_s);
	vertical_left.writeMicroseconds(vl_s);
	vertical_right.writeMicroseconds(vr_s);
	
}
