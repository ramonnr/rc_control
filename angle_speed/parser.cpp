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
#include "NewPing.h"

#define trigPin 5
#define echoPin 6
#define forward true
#define reverse false

void setSpeed(uint8_t,bool);
int setAngle(uint8_t);
void breakPulse();
void parser(byte[]);
void servoAttatch(void);
SoftwareServo servo;
static bool fwd=true;
static bool stop = false;
static bool dir;
static bool lastDir=reverse;
static bool first = true;
extern bool hasBreaked;



void breakPulse(){
	setSpeed(255,false);
	delay(200);
	setSpeed(0,false);
	hasBreaked=true;
}

void parser(byte input[]){


	uint8_t op=input[0];
	uint8_t ammount=input[1];
	bool dir=false;



	switch(op){
	case 200:

		servo.write(ammount);
		break;

	case 201:

		if(ammount>50 && !hasBreaked){
			dir=true;
			ammount=((ammount-50)*5.1);
			setSpeed(ammount,dir);
		}
		else if(ammount==50){
			ammount=0;
			setSpeed(ammount,dir);
		}
		else if(ammount<50){
			dir=false;
			hasBreaked=false;
			ammount=abs((ammount-50)*5.1);
			setSpeed(ammount,dir);
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
