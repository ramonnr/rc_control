// Do not remove the include below
#include "angle_speed.h"
#include "SoftwareServo.h"


//#include "parser.h"
#define servoPin 11
#define pwmPin 3
#define dirPin 2
#define buttonPin 7
#define trigPin 5
#define echoPin 6
#define honkPin 12
#define vSensPin A2
#define correctionPin A3
void parser(byte[]);
void servoAttatch(void);
void servoRefresh(void);
int setAngle(uint8_t angle);


uint8_t gCorrectionVal;
int speed=1;
bool refresh=false;
int limits[2] = {30,150};
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
	servoAttatch();


// Add your initialization code here
}
bool foundBuddy=false;
bool steeringCorrection=false;

// The loop function is called in an endless loop
void loop()
{
	servoRefresh();
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

	}/*else{
	output=(float) ((analogRead(vSensPin)*5.0/1023.0));
	Serial.print('#');
	Serial.print(output);
	Serial.print('@');
	}*/
//Add your repeated code here


	//Servo test code
	/*while(1){
		SoftwareServo::refresh();
		//straight test
		servo.write(90);
		delay(300);

		//sweeping test
		for(uint8_t i=0;i<=180;i+=60){
			SoftwareServo::refresh();
			servo.write(i);
			delay(500);
		}
		for(uint8_t i=180;i>=0;i-=60){
			SoftwareServo::refresh();
			servo.write(i);
			delay(500);
		}

	}*/
//	// refresh angle
//		int angle = servo.read();
//
//		// change direction when limits
//		if (angle >= limits[1] || angle <= limits[0])  speed = -speed;
//
//		servo.write(angle + speed);
//
//		// set refresh one time / 2
//		refresh = refresh ? false : true;
//		if (refresh) SoftwareServo::refresh();
//
//		Serial.print("Angle: ");
//		Serial.println(angle);

}
