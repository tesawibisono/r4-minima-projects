#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Constants for screen resolution and center point
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

// Global variables
volatile float panAngle = 90; // Initial pan angle
Servo panServo; // Servo for pan movement

DFRobot_HuskyLens huskylens; // HuskyLens object

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  
  panServo.attach(9); // Attach pan servo to pin 9
  
  huskylens.beginI2CUntilSuccess(); // Initialize I2C communication with HuskyLens
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Set algorithm to object tracking mode
  
  delay(2000); // Wait for HuskyLens to initialize
}

void loop() {
  // Request data from HuskyLens
  huskylens.request();
  
  // Read the position (xCenter, yCenter) of the detected object
  int xCenter = huskylens.readBlockParameter(1).xCenter;
  int yCenter = huskylens.readBlockParameter(1).yCenter;
  
  // Calculate the pan adjustment based on the object's position
  if (xCenter > SCREEN_CENTER_X + 20) { // If object is to the right of center
    panAngle -= 1.5; // Decrease pan angle
  } else if (xCenter < SCREEN_CENTER_X - 20) { // If object is to the left of center
    panAngle += 1.5; // Increase pan angle
  }
  
  // Constrain pan angle within valid range (0 to 180 degrees)
  panAngle = constrain(panAngle, 0, 180);
  
  // Update the pan servo position
  panServo.write(panAngle);
  
  delay(100); // Add a short delay to avoid rapid servo movements
}
