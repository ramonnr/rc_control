/********************HEADER******************************************
 *
 *   angle_speed.cpp
 *
 *   Created on: 22 apr 2015
 *       Authors:
 *       Ramón Rodriguez, Mikael André, Simon Johansson, Hannes Paulsson
 *
 *     S.A.R.A - Revamped
 *
 *     Main program to run an RC-car controlled by an
 *     Android application.
 *
 *     This code is written to be run on an
 *     Arduino UNO with the following outboard equipment:
 *
 *     - PKA03 MotorShield
 *     - HC-06 Bluetooth transceiver
 *     - HC-SR04 Ultrasoniv distance sensor
 *     - 5V DC-Servo
 *     - DC engine
 *
 *
 **************************************************************/

/*************INCLUDES*************/
#include "angle_speed.h"
#include "SoftwareServo.h"
#include "NewPing.h"

/************DEFINES*************/
#define servoPin 11
#define pwmPin 3
#define dirPin 2
#define trigPin 5
#define echoPin 6
#define honkPin 12
#define vSensPin A4
#define ledPin A0

/****************PROTOTYPES************/
void parser(byte[], int);
void servoAttatch(void);
void servoRefresh(void);
void breakPulse(void);
int setAngle(uint8_t angle);
int sensor(void);

/************GLOBAL VARIABLES*************/
float output;
int timer =0;
int recievedIndex = 0;
int distance = 500;
byte input[3];
boolean hasBreaked = false;
boolean started = false;


/************************************************
 * Arduino setup function
 *
 * Initiates:
 *  - input/output pins
 *  - servo
 *  - serial communication
 *
 *  LED on car is set to off.
 *
 *  Baud rate for serial communication is
 *  set to 9600 (default for Bluetooth device HC-06)
 *
 ***********************************************/
void setup()
{
	pinMode(servoPin,OUTPUT);
	pinMode(pwmPin,OUTPUT);
	pinMode(dirPin,OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(honkPin,OUTPUT);
	pinMode(vSensPin,INPUT);
	pinMode(ledPin, OUTPUT);
	Serial.begin(9600);
	servoAttatch();
	digitalWrite(A3, LOW);

}

/*****************************************************************************
 * Main loop.
 * Not much is actually done here.
 *
 * The servoRefresh function is called (required by SoftwareServo library)
 *
 * Battey voltage level is read and sent to serial port.
 * Voltage level sent via BlueTooth to Android Application.
 * Signs to help parser:
 * # = start sign
 * @ = end sign
 *
 ****************************************************************************/
void loop()
{
	servoRefresh();  //SoftwareServo function that must be called at leas every 20ms


	timer++;
	if(timer == 10000){
		output=(float) ((analogRead(vSensPin)*5.0/1023.0));

		Serial.print('#');
		Serial.print(output);
		Serial.print('@');
		timer = 0;
	}

}



/*********************************************************
 * serialEvent() is executed after each loop(), if there is serial data available.
 *
 * Serial data is read and used as argument to parser.
 * Incoming serial data will be on the format:
 * {[253],[key],[value][254]}
 * 253 = startsign
 * 254 = stopsign
 *
 *********************************************************/
void serialEvent(){

	if(Serial.available()){
		byte in = Serial.read();

		if(in == 254){
			parser(input, distance);
			input[0] = 0;
			input[1] = 0;
			input[2] = 0;
			started = 0;
			recievedIndex = 0;

		}else if(started){
			input[recievedIndex] = in;
			recievedIndex++;

		}else if(in == 253){
			started = true;

		}
	}
}





