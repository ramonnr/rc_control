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
static bool fwd=true;
static bool stop = false;
static bool dir;


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
uint8_t safeMode = input[3];
	//Serial.println(fwd);
	if(dist<50 && stop==false && dir==true && safeMode) {
		//Serial.println("false");
		fwd=false;
		stop=true;
		setSpeed(255,false);
		delay(150);
		setSpeed(0,false);

	}else if(dist<50 && stop==true && safeMode){
		fwd=false;
	}else{
		fwd=true;
		stop=false;
	}

	// angle is precomputed in adriod app
	uint8_t angle=(uint8_t)input[0];

	//static uint32_t toneMachine = 499;
	/*
	 * speed input:
	 *  0   is full speed dir -1
	 *  50  is full stop
	 *  100 is full speed dir 1
	 */
	uint8_t speed=(uint8_t) input[1];
	char honk=input[2];
	dir=false;

	if(honk>0){
		switch (honk){
		//Serial.println(honk);
		case 'A':tone(12,220,100);
		break;
		case 'B':tone(12,246.94,100);
		break;
		case 'C':tone(12,261.94,100);
		break;
		case 'D':tone(12,293.66,100);
		break;
		case 'E':tone(12,329.63,100);
		break;
		case 'F':tone(12,349.23,100);
		break;
		case 'G':tone(12,392,100);
		break;
		default: noTone(12);
		break;
		}
	}
	if(!honk){
		noTone(12);
		//toneMachine = 0;
	}
	if(speed>50 && fwd==true){
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

	}else{
		setSpeed(0,false);
	}
	//fall through for undefined behaviour, do nothing

	return;
}


