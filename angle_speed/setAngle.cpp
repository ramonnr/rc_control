/*
 * setAngle.cpp
 *
 *  Created on: 22 apr 2015
 *      Author: Rodriguez
 */
#include "servo.h"

Servo servo=Servo();
bool isFirstRun=true;

void setAngle(uint8_t angle){

	//save exec time, only attach on first run
	if(isFirstRun){
		//servo pin is 11
		servo.attach(11);
		isFirstRun=false;
	}
	servo.write(angle);
	return;
}



