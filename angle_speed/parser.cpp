/****************************************************************
 * parser.cpp
 *
 *  Created on: 22 apr 2015
 *      Authors:
 *      Ramón Rodriguez, Mikael André, Simon Johansson, Hannes Paulsson
 *
 *      This file contains the main functions to interpret and handle
 *      incoming serial data.
 *
 ****************************************************************/

/*************INCLUDES*************/
#include <stdbool.h>
#include <stdint.h>
#include <arduino.h>
#include "SoftwareServo.h"
#include "NewPing.h"

/************DEFINES*************/
#define trigPin 5
#define echoPin 6
#define forward true
#define reverse false


/****************PROTOTYPES************/
void setSpeed(uint8_t,bool);
int setAngle(uint8_t);
void breakPulse();
void parser(byte[], int);
void servoAttatch(void);
int getAvarageDistance(int inDist);


/************GLOBAL VARIABLES*************/
static bool fwd=true;
static bool useStopper = true;
static bool dir;
static bool lastDir=reverse;
static bool first = true;
extern bool hasBreaked;
int medianDistance[5];
uint32_t medianDistanceIndex = 0;


/************INITIATIONS********************/
NewPing sonar(trigPin, echoPin, 200);
SoftwareServo servo;



/*********************************************************
 * Break pulse is called by the automatic stop function
 * as long as the car is too close to the object in front
 * and the user is trying to drive forward
 ********************************************************/
void breakPulse(){
	setSpeed(255,false);
	delay(200);
	setSpeed(0,false);
	hasBreaked=true;
}


/*****************************************************************
 * The parser function is used to interpret incoming serial data
 * and act accordingly.
 * The input data will be on the form {[key],[value]}, where the key
 * defines the action to be performed.
 *
 * Keys:
 * 200 --->  Steering   - Value: angle
 * 201 --->  Engine     - Value: speed
 * 202 --->  DistSensor - Value : 100=off 101=on
 *
 *
 ********************************************************************/

void parser(byte input[], int distance){


	uint8_t op=input[0];
	uint8_t ammount=input[1];
	bool dir=false;

	distance = getAvarageDistance(distance); //Get average distance to avoid missreadings

	switch(op){
	case 200:

		servo.write(ammount);
		break;


	case 201:
		if(ammount>50){
			if(useStopper){
				if(distance<40 && distance > 5){
					breakPulse();
				}
				else{
					dir=true;
					ammount=((ammount-50)*5.1);
					setSpeed(ammount,dir);}
			}else{
				dir=true;
				ammount=((ammount-50)*5.1);
				setSpeed(ammount,dir);}
		}

		else if(ammount==50){
			setSpeed(0,dir);
		}
		else if(ammount<50){
			dir=false;
			ammount=abs((ammount-50)*5.1);
			setSpeed(ammount,dir);
		}
		break;


	case 202:
		if(ammount==101){
			useStopper=false;
			digitalWrite(ledPin,HIGH);
		}else if (ammount == 100){
			useStopper=true;
			digitalWrite(ledPin,LOW);
		}
	}


	return;
}

/*****************************************
 * Initiate servo and set wheels straight
 ****************************************/
void servoAttatch(){
	servo.attach(11);
	servo.write(90);
}


/*********************************************
 * SoftwareServo function called from mainloop
 ********************************************/
void servoRefresh(){
	SoftwareServo::refresh();
}


/******************************************************************
 * This function calculates the average distance based
 * on the last 5 inputs.
 *
 *  @return  distance in cm
 *****************************************************************/
int getAvarageDistance(int inDist){

	int tempDist = sonar.ping_cm();

		if(tempDist > 4)
		{
			medianDistance[medianDistanceIndex % 5] = tempDist;
			medianDistanceIndex++;
			inDist = 0;
			for(int i = 0; i < 5; i++) inDist += medianDistance[i];

			inDist = inDist / 5;
			if(medianDistanceIndex<5) inDist = 100; //To avoid bad values when the first 5 inputs are empty.
			return inDist;
		}

		else return 100;

}
