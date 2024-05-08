#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Global variables
volatile float mind_n_currentx = 0;
volatile float mind_n_currenty = 0;

// Create objects for servos
DFRobot_HuskyLens huskylens;
Servo servoPan; // Servo for pan movement
Servo servoTilt; // Servo for tilt movement

// Main program start
void setup() {
  // Attach servos to pins
  servoPan.attach(9); // Pan servo connected to pin 9
  servoTilt.attach(10); // Tilt servo connected to pin 10
  
  // Initialize HuskyLens
  Serial.begin(9600); // Initialize serial communication for debugging
  huskylens.beginI2CUntilSuccess(); // Initialize I2C communication with HuskyLens
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Set algorithm to object tracking mode
  delay(2000); // Wait for 1 second
  
  // Initialize initial servo positions
  mind_n_currentx = 90; // Initial pan position
  mind_n_currenty = 90; // Initial tilt position (centered)
  servoPan.write(mind_n_currentx); // Set initial position for pan servo
  servoTilt.write(mind_n_currenty); // Set initial position for tilt servo
}

void loop() {
  // Request data from HuskyLens
  huskylens.request();
  
  // Adjust servo positions based on object position
  int xCenter = huskylens.readBlockParameter(1).xCenter;
  int yCenter = huskylens.readBlockParameter(1).yCenter;

  // Pan movement
  if (xCenter > 190) {
    mind_n_currentx -= 1.5;
    servoPan.write(constrain(mind_n_currentx, 0, 180));
  } else if (xCenter > 10 && xCenter < 130) {
    mind_n_currentx += 1.5;
    servoPan.write(constrain(mind_n_currentx, 0, 180));
  }

  //**** Tilt movement
  //if (yCenter > 150) {
  //  mind_n_currenty += 1.0;
  //  servoTilt.write(constrain(mind_n_currenty, 0, 180)); // Ensure the tilt servo doesn't exceed its limits
  //} else if (yCenter > 10 && yCenter < 90) {
  //  mind_n_currenty -= 1.0;
  //  servoTilt.write(constrain(mind_n_currenty, 0, 180)); // Ensure the tilt servo doesn't exceed its limits
  //}

}
