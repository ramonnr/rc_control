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
int distance = 0;
NewPing sonar(trigPin, echoPin, 200);



void breakPulse(){
	setSpeed(255,false);
	delay(200);
	setSpeed(0,false);
	stop=true;
}

void parser(byte input[]){


	uint8_t op=input[0];
	uint8_t ammount=input[1];
	bool dir=false;



	switch(op){
	case 2:

		servo.write(ammount);
		break;

	case 1:

		if(ammount>50){
			distance = 100;//sonar.ping_cm();
			if(distance>30 && distance!=0){
				dir=true;
				ammount=((ammount-50)*5.1);
				setSpeed(ammount,dir);
				stop=false;
				return;
			}else if(!stop){
				breakPulse();
				return;
			}
			return;

		}
		else if(ammount==50){
			ammount=0;
			setSpeed(ammount,dir);
			return;
		}
		else if(ammount<50){
			dir=false;
			stop=false;
			ammount=abs((ammount-50)*5.1);
			setSpeed(ammount,dir);
			return;
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
