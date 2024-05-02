/* The HuskyLens module communicates using the I2C protocol,
 * so you should connect it to the Arduino's dedicated I2C pins.
 * On Arduino R4 Minima boards, these pins are labeled as SDA (data line)
 * and SCL (clock line). 
 * 
 * The pins used for I2C on the UNO R4 Minima are the following:
 * SDA - D18 or A4. SCL - D19 or A5.
 */

#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Pin Definitions
#define PAN_SERVO_PIN 9 //base
//** #define TILT_SERVO_PIN 10 //top

// Global Variables
Servo panServo;
//** Servo tiltServo;
DFRobot_HuskyLens huskyLens;

// Servo movement increment and delay
 const int SERVO_INCREMENT = 1; // Adjust as needed for smoother movement
 const int SERVO_DELAY = 15; // Delay in milliseconds between servo movements


void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Attach servos to pins
  panServo.attach(PAN_SERVO_PIN);
  //** tiltServo.attach(TILT_SERVO_PIN);

  // Initialize HuskyLens
  huskyLens.beginI2CUntilSuccess();
  huskyLens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Set algorithm to object tracking mode
  
  // Set initial position of servos
  panServo.write(90); // Center position
  //** tiltServo.write(90); // Center position

  delay(2000);
}

// Function to smoothly move the servo to the target angle
 void moveServoSmoothly(Servo& servo, int targetAngle) {
  int currentAngle = servo.read();
  while (currentAngle != targetAngle) {
    if (currentAngle < targetAngle) {
      currentAngle += SERVO_INCREMENT;
      if (currentAngle > targetAngle) currentAngle = targetAngle;
    } else {
      currentAngle -= SERVO_INCREMENT;
     if (currentAngle < targetAngle) currentAngle = targetAngle;
    }
    servo.write(currentAngle);
    delay(SERVO_DELAY);
  }
 } 


void loop() {
  // Request data from HuskyLens
  huskyLens.request();
  
  // Read object position
  int objectX = huskyLens.readBlockParameter(1).xCenter;
  int objectY = huskyLens.readBlockParameter(1).yCenter;

// Check if object is detected
  if (objectX == -1 && objectY == -1) {
    // Object not detected, move servos to initial position
    panServo.write(90); // Center position
    //** tiltServo.write(90); // Center position

    // Print servo angles (for debugging)
    //** Serial.println("Servo angles - Pan: 90, Tilt: 90 (Object not detected)");
  } 
  else {
  // Map object position to servo angles
  int panAngle = map(objectX, 0, 320, 180, 0); 
  //** int tiltAngle = map(objectY, 0, 240, 0, 180);

  // Constrain servo angles to valid range
  panAngle = constrain(panAngle, 0, 180);
  //** tiltAngle = constrain(tiltAngle, 0, 60);

  // Set servo angles
  panServo.write(panAngle);
  //** tiltServo.write(tiltAngle);

  // Move pan servo smoothly to the target angle
    moveServoSmoothly(panServo, panAngle);

  // Move tilt servo smoothly to the target angle
  //** moveServoSmoothly(tiltServo, tiltAngle);

  // Print object position (for debugging)
  Serial.print("Object Position - X: ");
  Serial.print(objectX);
  Serial.print(", Y: ");
  Serial.println(objectY);
  Serial.print("Servo angles - Pan: ");
  Serial.print(panAngle);
  Serial.print(", Tilt: ");
//**  Serial.println(tiltAngle);
  }
}
