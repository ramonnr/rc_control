// Do not remove the include below
#include "angle_speed.h"


//#include "parser.h"
#define servoPin 11
#define pwmPin 3
#define dirPin 2
#define buttonPin 7
#define trigPin 8
#define echoPin 9
#define honkPin 12
#define vSensPin A2
#define correctionPin A3
void parser(byte[]);
int setAngle(uint8_t angle);

uint8_t gCorrectionVal;


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
	pinMode(vSensPin,INPUT);
	pinMode(buttonPin,INPUT);
	pinMode(correctionPin,INPUT);
	Serial.begin(9600);
// Add your initialization code here
}
bool foundBuddy=false;
bool steeringCorrection=false;

// The loop function is called in an endless loop
void loop()
{
	/*
	if(!foundBuddy){
		foundBuddy);
		setAngle(30);
	}
	*/

	/*
	while(!steeringCorrection){
		delay(100);
		int bState=digitalRead(buttonPin);
		int correction=analogRead(correctionPin);
		//setAngle(130);
		//delay(500);
		if(bState==1){
			//Serial.println("down");
			//Serial.println(correction);
			correction= correction * 0.16;
			//Serial.println(correction);
			gCorrectionVal=(uint8_t) correction;
			setAngle(70,(uint8_t)correction);
			gCorrectionVal=(uint8_t) correction;
			//setAngle(correction);
			//steeringCorrection=true;
		}else{
		steeringCorrection=true;
		}
	}
	*/


	byte input[2];
	float output;
	if(Serial.available()>0){
		//if(!foundBuddy)foundBuddy=true;
		Serial.readBytes(input,2);
		//Serial.println(input[1]);
		parser(input);

	}else{
	output=(float) ((analogRead(vSensPin)*5.0/1023.0));
	Serial.print('#');
	Serial.print(output);
	Serial.print('@');
	}
//Add your repeated code here


	//Servo test code
	/*while(1){
		//straight test
		setAngle(120);

		//sweeping test
		/*for(uint8_t i=0;i<=180;i+=60){
			setAngle(i);
			delay(500);
		}
		for(uint8_t i=180;i>=0;i-=60){
			setAngle(i);
			delay(500);
		}

	}
 */

}
