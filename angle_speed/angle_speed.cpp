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

/*
long sensor2(){
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
*/
//The setup function is called once at startup of the sketch
void setup()
{
	//Serial.println("hello");
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

	//int dist=(int)sensor2();
	//Serial.println(dist);


	byte input[2];
	//Serial.begin(9600);
	if(Serial.available()>0){
		Serial.readBytes(input,2);


		//Serial.println();
		//delay(500);
		parser(input);
		//Serial.end();
	}

//Add your repeated code here
}
