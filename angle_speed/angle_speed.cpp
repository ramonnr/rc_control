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
	//Serial.begin(9600);
	servoRefresh();
	//distance = sonar.ping_cm();


			//Serial.println(distance);

//			if(distance < 30 && distance != 0 && !stop){ breakPulse();
//			}else if(distance < 30 && distance != 0&& stop){ }
//			else {stop=false;}


	byte input[2];
	float output;
	if(Serial.available()>0){
		//if(!foundBuddy)foundBuddy=true;
		Serial.readBytes(input,2);
		//Serial.println(input[1]);
		parser(input);
		//Serial.flush();
		//Serial.end();

	}else{


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
//Add your repeated code here

}


int sensor(){
	//int echoTime = sonar.ping();
	//int distance= NewPingConvert(echoTime, US_ROUNDTRIP_CM);
//	digitalWrite(trigPin, LOW);
//	delayMicroseconds(2);
//	digitalWrite(trigPin, HIGH);
//	delayMicroseconds(10);
//	digitalWrite(trigPin, LOW);
//	digitalWrite(echoPin, HIGH);
//	duration = pulseIn(echoPin, HIGH, 50);
//	distance = (duration/2) / 29.1;

	//return distance;
}


