/*
 * parser.cpp
 *
 *  Created on: 22 apr 2015
 *      Author: Rodriguez
 */
#include <stdbool.h>
#include <stdint.h>
#include <arduino.h>
#include "SoftwareServo.h"

#define trigPin 5
#define echoPin 6
#define forward true
#define reverse false

void setSpeed(uint8_t,bool);
int setAngle(uint8_t);
int sensor(void);
void breakPulse();
void parser(byte[]);
void servoAttatch(void);
SoftwareServo servo;

static bool fwd=true;
static bool stop = false;
static bool dir;
static bool lastDir=reverse;
static bool first = true;


int sensor(){
	int duration;
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
//int dist = sensor();
//	if(dist<20){
//		digitalWrite(7,HIGH);
//	}else{digitalWrite(7,LOW);
//	}

	/*
	if(dist<20){
		breakPulse();
		return;
	}
	 */
	int vals;

	//servo.write(70);

	switch(op){
	case 2:
		servo.write(ammount);
		//		vals =  setAngle(ammount);
		//		if(vals != ammount) Serial.println((int) vals);
		break;

	case 1:
		if(ammount>50){
			digitalWrite(7,HIGH);
			dir=true;
			ammount=((ammount-50)*5.1);
			setSpeed(ammount,dir);
			return;
		}
		else if(ammount==50){
			ammount=0;
			setSpeed(ammount,dir);
			return;
		}
		else if(ammount<50){
			dir=false;
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

void servoAttatch(){
	servo.attach(11);
	servo.write(90);
}

void servoRefresh(){
	SoftwareServo::refresh();
}
