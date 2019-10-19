/*
 * Bu Robotics Zumo Build Template
 */

//Board Inclusions
#include <stdlib.h>
#include <Wire.h>
#include <Zumo32U4.h>


//Needed Components
Zumo32U4LCD lcd;
Zumo32U4ButtonB buttonB;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

//Time Variable, sensor detection
#define sensorThreshold  1000 //microseconds

// These might need to be tuned for different motor types.
#define REVERSE_SPEED     300  // 0 is stopped, 400 is full speed
#define TURN_SPEED        300
#define FORWARD_SPEED     300
#define REVERSE_DURATION  200  // ms
#define TURN_DURATION     300  // ms


//Number of line sensor used, sets values into an array 0 being the leftmost last array value being rightmost
#define NUM_SENSORS 3
unsigned int lineSensorValues[NUM_SENSORS];

void setup() {
  // put your setup code here, to run once:
  
  lineSensors.initThreeSensors();
  lcd.clear();
  lcd.print(F("Press B"));
  buttonB.waitForButton();
    // Play audible countdown.
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
    lineSensors.read(lineSensorValues);

  if (lineSensorValues[0] < sensorThreshold)
  {
    // If leftmost sensor detects line, reverse and turn to the
    // right.
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (lineSensorValues[NUM_SENSORS - 1] < sensorThreshold)
  {
    // If rightmost sensor detects line, reverse and turn to the
    // left.
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else
  {
    // Otherwise, go straight.
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}
