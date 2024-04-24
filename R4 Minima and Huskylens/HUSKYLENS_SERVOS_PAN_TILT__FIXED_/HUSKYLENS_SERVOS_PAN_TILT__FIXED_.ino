/*****************************************
The HuskyLens module communicates using the I2C protocol,
so you should connect it to the Arduino's dedicated I2C pins.
On most Arduino boards, these pins are labeled as SDA (data line)
and SCL (clock line). 
 
The pins used for I2C on the UNO R4 Minima are the following:
SDA - D18 or A4. SCL - D19 or A5.
*****************************************/

#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

//HUSKYLENS green line >> SDA; blue line >> SCL
// Pins for the servos
#define PAN_SERVO_PIN 9
#define TILT_SERVO_PIN 10

// Create servo objects
Servo panServo;
Servo tiltServo;

// Create HuskyLens object
DFRobot_HuskyLens huskylens;

// Variables to store object position
int objectX = 0;
int objectY = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach servos to pins
  panServo.attach(PAN_SERVO_PIN);
  tiltServo.attach(TILT_SERVO_PIN);

  // Initialize HuskyLens communication
  huskylens.beginI2CUntilSuccess();
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);

  // Set initial servo positions
  panServo.write(90); // Center position for pan servo
  tiltServo.write(90); // Center position for tilt servo
}

void loop() {
  // Request data from HuskyLens
  huskylens.request();

  // Get object position from HuskyLens
  objectX = huskylens.readBlockParameter(1).xCenter;
  objectY = huskylens.readBlockParameter(1).yCenter;

  // Print object position (for debugging)
  Serial.print("Object X: ");
  Serial.print(objectX);
  Serial.print(", Object Y: ");
  Serial.println(objectY);

  // Map object position to servo angles
  int panAngle = map(objectX, 0, 319, 0, 180); // Map X position to pan servo angle
  int tiltAngle = map(objectY, 0, 239, 180, 0); // Map Y position to tilt servo angle

  // Constrain servo angles to prevent exceeding limits
  panAngle = constrain(panAngle, 0, 180);
  tiltAngle = constrain(tiltAngle, 0, 180);

  // Move servos to track the object
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);

  // Delay for stability
  delay(100); // Adjust as needed based on servo responsiveness
}
