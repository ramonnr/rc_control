// Do not remove the include below
#include "angle_speed.h"
#include "SoftwareServo.h"
#include "NewPing.h"


//#include "parser.h"
#define servoPin 11
#define pwmPin 3
#define dirPin 2
#define trigPin 5
#define echoPin 6
#define honkPin 12
#define vSensPin A5


void parser(byte[]);
void servoAttatch(void);
void servoRefresh(void);
void breakPulse(void);
int setAngle(uint8_t angle);
int sensor(void);
int timer;
int recievedIndex = 0;
int distance = 0;
NewPing sonar(trigPin, echoPin, 200);
byte input[2];

boolean hasBreaked = false;
boolean started = false;


//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(servoPin,OUTPUT);
	pinMode(pwmPin,OUTPUT);
	pinMode(dirPin,OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(honkPin,OUTPUT);
	pinMode(vSensPin,INPUT);
	pinMode(A3, OUTPUT);
	Serial.begin(9600);
	servoAttatch();
	analogWrite(A3, 0);
	timer = 0;


// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
	servoRefresh();

	distance = sonar.ping_cm();

	//Serial.print(distance);

	if(distance != 0){
		if(distance < 40){
			if(!hasBreaked) breakPulse();
			hasBreaked = true;

		}
	}
	if(distance > 40 || distance == 0){
		hasBreaked = false;
	}

	/*
	byte input[2];
	float output;
	if(Serial.available()>0){
		Serial.readBytes(input,2);
		parser(input);

	}else{

*/
//	timer++;
//	if(timer == 100000){
//		output=(float) ((analogRead(vSensPin)*5.0/1023.0));
//
//		Serial.print('#');
//		Serial.print(output);
//		Serial.print('@');
////		timer = 0;
//		}

	}

void serialEvent(){


	if(Serial.available()){
		byte in = Serial.read();

		if(in == 254){ //254 = stoptecken
			parser(input);
			input[0] = 0;
			input[1] = 0;
			started = 0;
			recievedIndex = 0;
		}else if(started){
			input[recievedIndex] = in;
			recievedIndex++;
		}else if(in == 253){ //253 = starttecken
			started = true;
		}
	}
}
//Add your repeated code here




