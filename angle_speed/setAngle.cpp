/*
 * setAngle.cpp
 *
 *  Created on: 22 apr 2015
 *      Author: Rodriguez
 */
#include "servo.h"
#include "arduino.h"

Servo servo=Servo();
bool isFirstRun=true;
extern uint8_t gCorrectionVal;

int setAngle(uint8_t angle){
//Serial.begin(9600);

	//save exec time, only attach on first run
	if(isFirstRun){
		//servo pin is 11
		servo.attach(11, 1000, 2000);
		isFirstRun=false;
	}
	//Serial.println((angle+gCorrectionVal));
	servo.write((uint8_t)(angle));
	return servo.read();
}



