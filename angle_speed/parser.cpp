/*
 * parser.cpp
 *
 *  Created on: 22 apr 2015
 *      Author: Rodriguez
 */
#include <stdbool.h>
#include <stdint.h>
#include <arduino.h>

#define trigPin 8
#define echoPin 9

void setSpeed(uint8_t,bool);
void setAngle(uint8_t);
long sensor(void);

long sensor(){
	 long duration, distance;
	  digitalWrite(trigPin, LOW);
	  delayMicroseconds(2);
	  digitalWrite(trigPin, HIGH);
	  delayMicroseconds(10);
	  digitalWrite(trigPin, LOW);
	  duration = pulseIn(echoPin, HIGH);
	  distance = (duration/2) / 29.1;
	  return distance;
}

void parser(byte input[]){
	long dist=sensor();
		while(dist<20) {
			setSpeed(0,false);
			dist=sensor();

	}
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


