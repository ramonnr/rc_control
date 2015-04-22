/*
 * parser.cpp
 *
 *  Created on: 22 apr 2015
 *      Author: Rodriguez
 */
#include <stdbool.h>
#include <stdint.h>
#include <arduino.h>

void setSpeed(uint8_t,bool);
void setAngle(uint8_t);


void parser(byte input[]){

	 // angle is precomputed in adriod app
	uint8_t angle=(uint8_t)input[0];

	/*
	 * speed input:
	 *  0   is full speed dir -1
	 *  50  is full stop
	 *  100 is full speed dir 1
	 */
	uint8_t speed=(uint8_t) input[1];
	bool dir=false;
	if(speed>50){
		dir=true;
		speed=(speed-50)*5.1;
		setSpeed(speed,dir);
		setAngle(angle);
		return;
	}
	else if(speed==50){
		speed=0;
		setSpeed(speed,dir);
		setAngle(angle);
		return;
	}
	else if(speed<50){
		speed=abs((speed-50)*5.1);
		setSpeed(speed,dir);
		setAngle(angle);
		return;
	}
	//fall through for undefined behaviour, do nothing

	return;
}


