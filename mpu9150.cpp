////////////////////////////////////////////////////////////////////////////
//
//  This file is part of MPU9150Lib
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "I2Cdev.h"
#include "MPU9150Lib.h"
#include "CalLib.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include <EEPROM.h>
#include <Arduino.h>
#include "timer.h"
#include "Wire.h"
#include "misc.h"
#include "slconfig.h"
MPU9150Lib MPU;                                              // the MPU object

boolean isInited = false;

//  MPU_UPDATE_RATE defines the rate (in Hz) at which the MPU updates the sensor data and DMP output

#define MPU_UPDATE_RATE  (20)

//  MPU_MAG_MIX defines the influence that the magnetometer has on the yaw output.
//  The magnetometer itself is quite noisy so some mixing with the gyro yaw can help
//  significantly. Some example values are defined below:

#define  MPU_MAG_MIX_GYRO_ONLY          0                   // just use gyro yaw
#define  MPU_MAG_MIX_MAG_ONLY           1                   // just use magnetometer and no gyro yaw
#define  MPU_MAG_MIX_GYRO_AND_MAG       10                  // a good mix value 
#define  MPU_MAG_MIX_GYRO_AND_SOME_MAG  50                  // mainly gyros with a bit of mag correction 

void mpu9150_update() {
	if (MPU.read()) {                                        // get the latest data if ready yet

		SLSERIAL.print("MPU9150(");
		SLSERIAL.print(MPU.m_fusedEulerPose[VEC3_X] * RAD_TO_DEGREE);
		SLSERIAL.print(",");
		SLSERIAL.print(MPU.m_fusedEulerPose[VEC3_Y] * RAD_TO_DEGREE);
		SLSERIAL.print(",");
		SLSERIAL.print(MPU.m_fusedEulerPose[VEC3_Z] * RAD_TO_DEGREE);
		SLSERIAL.println(")");
	}
}

void mpu9150_setup()
{
	Wire.begin();

	if(!MPU.init(MPU_UPDATE_RATE, MPU_MAG_MIX_GYRO_AND_MAG)) {
		Serial.println(F("log(\"Init MPU9150 failed\")"));
	} else {
		isInited = true;
		Serial.println(F("log(\"init on primary addresses ok\")"));
	}  
	timer::getInstance()->add_timer(5000,TIMER_REPEAT,mpu9150_update);
}

