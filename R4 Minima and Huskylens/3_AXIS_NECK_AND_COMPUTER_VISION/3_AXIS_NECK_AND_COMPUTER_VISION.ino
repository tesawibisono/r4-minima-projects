#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Pins for the servos
#define PAN_SERVO_PIN 9
#define TILT_SERVO_PIN_1 10
#define TILT_SERVO_PIN_2 11

// Create servo objects
Servo panServo;
Servo tiltServo1;
Servo tiltServo2;

// Create HuskyLens object
DFRobot_HuskyLens huskylens;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach servos to pins
  panServo.attach(PAN_SERVO_PIN);
  tiltServo1.attach(TILT_SERVO_PIN_1);
  tiltServo2.attach(TILT_SERVO_PIN_2);

  // Initialize HuskyLens communication
  huskylens.beginI2CUntilSuccess();
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
}

void loop() {
  // Request data from HuskyLens
  huskylens.request();

  // Check if human is recognized
  if (huskylens.isAppear(1, HUSKYLENSResultBlock)) { // Assuming human is detected with ID 1
    // Get human position from HuskyLens
    int humanX = huskylens.readBlockParameter(1).xCenter;
    int humanY = huskylens.readBlockParameter(1).yCenter;

    // Map human position to servo angles
    int panAngle = map(humanX, 0, 319, 0, 180); // Map X position to pan servo angle
    int tiltAngle1 = map(humanY, 0, 239, 180, 0); // Map Y position to tilt servo 1 angle
    int tiltAngle2 = tiltAngle1; // Both tilt servos move together

    // Move servos to track the human
    panServo.write(panAngle);
    tiltServo1.write(tiltAngle1);
    tiltServo2.write(tiltAngle2);
  } else {
    // If human is not recognized, keep the servos in a neutral position
    panServo.write(90); // Center position for pan servo
    tiltServo1.write(90); // Center position for tilt servo 1
    tiltServo2.write(90); // Center position for tilt servo 2
  }

  // Delay for stability
  delay(100); // Adjust as needed based on servo responsiveness
}
