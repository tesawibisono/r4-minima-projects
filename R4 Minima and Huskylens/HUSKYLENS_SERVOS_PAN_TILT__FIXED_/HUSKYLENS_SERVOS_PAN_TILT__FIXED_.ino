/*****************************************
The HuskyLens module communicates using the I2C protocol,
so you should connect it to the Arduino's dedicated I2C pins.
On most Arduino boards, these pins are labeled as SDA (data line)
and SCL (clock line). 
 
The pins used for I2C on the UNO R4 Minima are the following:
SDA - D18 or A4. SCL - D19 or A5.

Huskylens Connection
Blue - SCL
Green - SDA
*****************************************/

#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Global variables
volatile float mind_n_currentx = 0;
volatile float mind_n_currenty = 0;

// Create an object
DFRobot_HuskyLens huskylens;
Servo servo_9;
Servo servo_10;

// Main program start
void setup() {
  // Attach servos to pins
  servo_9.attach(9); // Pan servo connected to pin 9
  servo_10.attach(10); // Tilt servo connected to pin 10
  
  // Initialize HuskyLens
  Serial.begin(9600); // Initialize serial communication for debugging
  huskylens.beginI2CUntilSuccess(); // Initialize I2C communication with HuskyLens
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Set algorithm to object tracking mode
  delay(1000); // Wait for 1 second
  
  // Initialize initial servo positions
  mind_n_currentx = 40;
  mind_n_currenty = 150;
  servo_9.write(mind_n_currentx); // Set initial position for servo_9
  servo_10.write(mind_n_currenty); // Set initial position for servo_10
}

void loop() {
  // Request data from HuskyLens
  huskylens.request();
  
  // Adjust servo positions based on object position
  int xCenter = huskylens.readBlockParameter(1).xCenter;
  int yCenter = huskylens.readBlockParameter(1).yCenter;

// Pan Movement
  if (xCenter > 190) {
    mind_n_currentx -= 1.5;
    servo_9.write(constrain(mind_n_currentx, 0, 120));
    
  } else if (xCenter > 10 && xCenter < 130) {
    mind_n_currentx += 1.5;
    servo_9.write(constrain(mind_n_currentx, 0, 120));
  }

// Tilt Movement
  if (yCenter > 150) {
    mind_n_currenty += 1.0;
    servo_10.write(constrain(mind_n_currenty, 0, 180));
  } else if (yCenter > 10 && yCenter < 90) {
    mind_n_currenty -= 1.0;
    servo_10.write(constrain(mind_n_currenty, 0, 180));
  }

  delay(100); // Adjust delay as needed
}
