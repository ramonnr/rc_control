// Do not remove the include below
#include "angle_speed.h"
//#include "parser.h"
#define servoPin 11
#define pwmPin 3
#define dirPin 2
#define trigPin 8
#define echoPin 9
#define honkPin 12
void parser(byte[]);

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.println("hello");
	pinMode(servoPin,OUTPUT);
	pinMode(pwmPin,OUTPUT);
	pinMode(dirPin,OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(honkPin,OUTPUT);
	Serial.begin(9600);
// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
	byte input[3];
	if(Serial.available()>0){
		Serial.readBytes(input,3);
		//Serial.println(input[0]);
		//Serial.println(input[1]);
		//Serial.println(input[2]);
		//Serial.println();
		//Serial.println("b1: %i",input[0]);
		//Serial.println("b2: %i",input[1]);
		parser(input);
	}

//Add your repeated code here
}
