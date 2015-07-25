#ifndef __SLTIMER__
#define __SLTIMER__
#include <arduino.h>

typedef void (*timer_callback)();
#define TIMER_REPEAT 32767
struct _timer_element {
	unsigned long outtime;
	unsigned long intervaltime;
	int times;
	timer_callback _func;
};


class timer {
public:
	timer(){
		_elemcount = 0;
		_pos = 0;
	}
	virtual ~timer(){}
	
	bool add_timer(unsigned long interval,int tis,timer_callback _call);
	
	bool run();
	
	static timer* getInstance();
private:
	_timer_element _time[32];
	byte _elemcount;
	byte _pos;
};
#endif

