/* The HuskyLens module communicates using the I2C protocol,
 * so you should connect it to the Arduino's dedicated I2C pins.
 * On most Arduino boards, these pins are labeled as SDA (data line)
 * and SCL (clock line). 
 * 
 * The pins used for I2C on the UNO R4 Minima are the following:
 * SDA - D18 or A4. SCL - D19 or A5.
 */

#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Pin Definitions
#define PAN_SERVO_PIN 9
#define TILT_SERVO_PIN 10

// Global Variables
Servo panServo;
Servo tiltServo;
DFRobot_HuskyLens huskyLens;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Attach servos to pins
  panServo.attach(PAN_SERVO_PIN);
  tiltServo.attach(TILT_SERVO_PIN);

  // Initialize HuskyLens
  huskyLens.beginI2CUntilSuccess();
  huskyLens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Set algorithm to object tracking mode
  
  // Set initial position of servos
  panServo.write(90); // Center position
  tiltServo.write(90); // Center position

  delay(2000);
}

void loop() {
  // Request data from HuskyLens
  huskyLens.request();
  
  // Read object position
  int objectX = huskyLens.readBlockParameter(1).xCenter;
  int objectY = huskyLens.readBlockParameter(1).yCenter;

  // Map object position to servo angles
  int panAngle = map(objectX, 0, 320, 0, 180); 
  int tiltAngle = map(objectY, 0, 240, 0, 180);

  // Constrain servo angles to valid range
  panAngle = constrain(panAngle, 0, 180);
  tiltAngle = constrain(tiltAngle, 0, 180);

  // Set servo angles
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
  
  
  // Print object position (for debugging)
  Serial.print("Object Position - X: ");
  Serial.print(objectX);
  Serial.print(", Y: ");
  Serial.println(objectY);
}
