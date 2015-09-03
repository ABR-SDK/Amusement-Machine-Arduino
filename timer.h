#ifndef __SLTIMER__
#define __SLTIMER__
#include <Arduino.h>

#define SEC_PER_MIN 60
#define SEC_PER_HOUR 3600
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


class ElapseTimer {

  private:
    unsigned long start;
    unsigned long last;

  public:
    ElapseTimer();
    unsigned long now() { return millis(); }
    boolean elapsed(unsigned long milliseconds);
    void reset();

};
#endif

