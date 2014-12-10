#include <Arduino.h>
#include <Constants.h>
#include <Fan.h>

#define SPEED_INTERVAL 350
#define SLOW_INTERVAL 150
#define SPEED_UP_BY 5
#define SLOW_DOWN_BY 10

Fan::Fan() {
}

void Fan::init() {
	fanMotor.attach(FAN_MOTOR_PIN);
	arm();
	prevMillis = millis();
}

void Fan::speedUp() {
	if(curSpeed < 80 && millis() >= (prevMillis + SPEED_INTERVAL)) {
		setSpeed(curSpeed + 5);
		prevMillis = millis();
	}
}

void Fan::slowDown() {
	if(curSpeed > 0 && millis() >= (prevMillis + SLOW_INTERVAL)) {
		setSpeed(curSpeed - 5);
		prevMillis = millis();
	}
}

int Fan::getSpeed() {
	return curSpeed;
}

boolean Fan::isStopped() {
	return curSpeed == 0;
}

boolean Fan::isAtMaxSpeed() {
	return curSpeed == 80;
}

void Fan::arm() {
	setSpeed(0);
}

void Fan::setSpeed(int speed){
  // speed is from 0 to 100 where 0 is off and 100 is maximum speed
  //the following maps speed values of 0-100 to angles from 0-180,
  // some speed controllers may need different values, see the ESC instructions
  curSpeed = speed;
  int angle = map(speed, 0, 100, 0, 180);
  fanMotor.write(angle);    
}