/*
 * setSpeed.cpp
 *
 *  Created on: 22 apr 2015
 *      Author: Rodriguez
 */
#include<stdbool.h>
#include<stdint.h>
#include<wiring_private.h>

#define dirPin 2
#define pwmPin 3

//using port A on motorshield
void setSpeed(uint8_t speed,bool dir){

	if(dir){
		digitalWrite(dirPin,HIGH);
	}

	else{
		digitalWrite(dirPin,LOW);
	}

	analogWrite(pwmPin,speed);

	return;
}


