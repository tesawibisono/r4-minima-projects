
// Include libraries and global variables
#include <SoftwareSerial.h>
#include <DFRobot_HuskyLens.h>
#include <Servo.h>

// Pin Definitions
#define PIN_SERVO_9 9 // Pin number for servo motor 9
#define PIN_SERVO_10 10 // Pin number for servo motor 10

// Initial angles for servo motors
#define INITIAL_ANGLE_SERVO_9 90 // Initial angle for servo motor 9
#define INITIAL_ANGLE_SERVO_10 90 // Initial angle for servo motor 10

// Global Variables
Servo servo_9; // Declare servo object for motor 9
Servo servo_10; // Declare servo object for motor 10
DFRobot_HuskyLens huskylens; // Declare HuskyLens object

float mind_n_currentx = 90; // Initialize current x position
float mind_n_currenty = 90; // Initialize current y position

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Initialize HuskyLens sensor
    huskylens.beginI2CUntilSuccess();
    huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Set algorithm to object tracking mode

    // Attach servo motors to pins
    servo_9.attach(PIN_SERVO_9);
    servo_10.attach(PIN_SERVO_10);

    // Set initial position of servo motors if needed
    servo_9.write(INITIAL_ANGLE_SERVO_9);
    servo_10.write(INITIAL_ANGLE_SERVO_10);
}


void loop() {
    huskylens.request();

    int xCenter = huskylens.readBlockParameter(1).xCenter;
    int yCenter = huskylens.readBlockParameter(1).yCenter;

    if (xCenter > 190) {
        mind_n_currentx -= 1.5;
        mind_n_currentx = constrain(mind_n_currentx, 0, 180);
        servo_9.write(mind_n_currentx);
    }
    else if (xCenter > 10 && xCenter < 130) {
        mind_n_currentx += 1.5;
        mind_n_currentx = constrain(mind_n_currentx, 0, 180);
        servo_9.write(mind_n_currentx);
    }

    if (yCenter > 150) {
        mind_n_currenty += 1.0;
        mind_n_currenty = constrain(mind_n_currenty, 0, 180);
        servo_10.write(mind_n_currenty);
    }
    else if (yCenter > 10 && yCenter < 90) {
        mind_n_currenty -= 1;
        mind_n_currenty = constrain(mind_n_currenty, 0, 180);
        servo_10.write(mind_n_currenty);

    // Print object position (for debugging)
    Serial.print("Object Position - X: ");
    Serial.print(objectX);
    Serial.print(", Y: ");
    Serial.println(objectY);
    Serial.print("Servo angles - Pan: ");
    Serial.print(panAngle);
    Serial.print(", Tilt: ");
    Serial.println(tiltAngle);
    }
}
