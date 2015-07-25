#include "timer.h"


bool timer::add_timer(unsigned long interval,int tis,timer_callback _call) {
	_timer_element* elem = NULL;
	
	for(int i = 0; i < _elemcount; i++) {
		if(_time[i].times < 0)
			elem = &_time[i];
	}

	if(elem == NULL) {
		if(_elemcount >= 32)
			return false;
		elem = &_time[_elemcount];
		_elemcount++;
	}
	elem->outtime = millis() + interval;
	elem->intervaltime = interval;
	elem->times = tis;
	elem->_func = _call;
}
	
bool timer::run() {
	
	byte r_times = _elemcount;
	_timer_element* elem = NULL;
	unsigned long nowtime = millis();
	
	while(r_times--) {

		if(_time[_pos].times > 0&&_time[_pos].outtime < nowtime) {
			elem = &_time[_pos++];
			if(_pos >= _elemcount) _pos = 0;
			break;
		}
		_pos++;
		if(_pos >= _elemcount) _pos = 0;
	}
	
	if(elem != NULL) {

		if(elem->times != TIMER_REPEAT) {
			elem->times -= 1;
		}
		elem->outtime = millis() + elem->intervaltime;
		if(elem->_func)
			elem->_func();
		return true;
	}
	
	return false;
}

timer _ins_timer;

timer* timer::getInstance() {
	return &_ins_timer;
}

