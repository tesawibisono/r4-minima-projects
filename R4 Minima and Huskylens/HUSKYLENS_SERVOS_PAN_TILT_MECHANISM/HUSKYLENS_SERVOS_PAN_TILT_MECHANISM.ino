/*!
 * Moving Servos with Huskylens Object Recognition
 * 
 * VIDEO TUTORIAL: https://www.youtube.com/watch?v=k-LXs94nRaU
 * by Maker Tutor
 * 
 * The HuskyLens module communicates using the I2C protocol,
 * so you should connect it to the Arduino's dedicated I2C pins.
 * On most Arduino boards, these pins are labeled as SDA (data line)
 * and SCL (clock line). 
 * 
 * The pins used for I2C on the UNO R4 Minima are the following:
 * SDA - D18 or A4. SCL - D19 or A5.
 */
#include <DFRobot_Servo.h>
#include <DFRobot_HuskyLens.h>

// Dynamic variables
volatile float mind_n_currentx, mind_n_currenty;
// Create an object
DFRobot_HuskyLens huskylens;
Servo             servo_9;
Servo             servo_10;


// Main program start
void setup() {
	servo_9.attach(9);
	servo_10.attach(10);
	huskylens.writeOSD(String("wating..."), 230, 35);
	huskylens.beginI2CUntilSuccess();
	huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
	delay(1000);
	huskylens.writeOSD(String("ok"), 230, 35);
	mind_n_currentx = 40;
	mind_n_currenty = 150;
	servo_9.angle(abs(mind_n_currentx));
	servo_10.angle(abs(mind_n_currenty));
}
void loop() {
	huskylens.request();
	huskylens.writeOSD(String(huskylens.readBlockParameter(1).xCenter), 230, 35);
	if ((huskylens.readBlockParameter(1).xCenter>190)) {
		mind_n_currentx -= 1.5;
		servo_9.angle(abs((constrain(mind_n_currentx, 0, 120))));
	}
	else if (((huskylens.readBlockParameter(1).xCenter>10) && (huskylens.readBlockParameter(1).xCenter<130))) {
		mind_n_currentx += 1.5;
		servo_9.angle(abs((constrain(mind_n_currentx, 0, 120))));
	}
	if ((huskylens.readBlockParameter(1).yCenter>150)) {
		mind_n_currenty += 1.0;
		servo_10.angle(abs((constrain(mind_n_currenty, 0, 120))));
	}
	else if (((huskylens.readBlockParameter(1).yCenter>10) && (huskylens.readBlockParameter(1).yCenter<90))) {
		mind_n_currenty -= 1;
		servo_10.angle(abs((constrain(mind_n_currenty, 0, 120))));
	}
}
