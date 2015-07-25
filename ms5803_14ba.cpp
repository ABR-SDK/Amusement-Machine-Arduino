#include "SparkFun_MS5803_I2C.h"
#include "misc.h"
#include <arduino.h>
#include "timer.h"
#include "slconfig.h"

MS5803 sensor(ADDRESS_LOW);

void ms5803_14ba_update() {
	float temp,press;
	temp = sensor.getTemperature(CELSIUS, ADC_512);
	press = sensor.getPressure(ADC_4096);
	
	if(temp < -100)
		temp = 0;
	if(press < -100)
		press = 0;
	
	SLSERIAL.print("ms5803(");
	SLSERIAL.print(temp);
	SLSERIAL.print(",");
	SLSERIAL.print(press);
	SLSERIAL.println(")");
}

void ms5803_setup() {	
	sensor.reset();
    sensor.begin();
	timer::getInstance()->add_timer(5000,TIMER_REPEAT,ms5803_14ba_update);
}