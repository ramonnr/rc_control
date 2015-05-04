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
#define forward true
#define reverse false

void setSpeed(uint8_t,bool);
void setAngle(uint8_t);
long sensor(void);
void breakPulse();

static bool fwd=true;
static bool stop = false;
static bool dir;
static bool lastDir=reverse;


long sensor(){
	long duration;
	int distance;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration/2) / 29.1;
	return distance;
}

void breakPulse(){
	setSpeed(255,false);
	delay(200);
	setSpeed(0,false);
}

void parser(byte input[]){

	uint8_t op=input[0];
	uint8_t ammount=input[1];
	bool dir=false;

	/*
	long dist=sensor();

	if(dist<20){
		breakPulse();
		return;
	}
	*/

	switch(op){
	case 2:
		setAngle(ammount);
		break;

	case 1:
		if(ammount>50){
			dir=true;
			ammount=(ammount-50)*5.1;
			setSpeed(ammount,dir);
			return;
		}
		else if(ammount==50){
			ammount=0;
			setSpeed(ammount,dir);
			return;
		}
		else if(ammount<50){
			ammount=abs((ammount-50)*5.1);
			setSpeed(ammount,dir);
			return;
		}
		break;
	case 3:
		switch (ammount){
		case 'A':tone(12,220);
		break;
		case 'B':tone(12,246.94);
		break;
		case 'C':tone(12,261.94);
		break;
		case 'D':tone(12,293.66);
		break;
		case 'E':tone(12,329.63);
		break;
		case 'F':tone(12,349.23);
		break;
		case 'G':tone(12,392);
		break;
		default: noTone(12);
		break;
		}
		break;
	}

	return;
}


