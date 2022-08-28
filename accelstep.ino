#include <AccelStepper.h>
 
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPinx 5
#define stepPinx 2
#define dirPiny 6
#define stepPiny 3
#define motorInterfaceType 1
//
const int trigPin = 22;
const int echoPin = 24;
// defines variables
long duration;
int distance;
const int distanceMin = 10;

bool vhcalligned = false;
 
// Create a new instance of the AccelStepper class:
AccelStepper stepperx = AccelStepper(motorInterfaceType, stepPinx, dirPinx);
AccelStepper steppery = AccelStepper(motorInterfaceType, stepPiny, dirPiny);
 
void setup() {
  // Set the maximum speed in steps per second:
  stepperx.setMaxSpeed(1000);
  steppery.setMaxSpeed(1000);
  Serial.begin(9600);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
 
void loop() 
{ 
//    vehicle = Serial.read();
//    Serial.println(vehicle);

// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.println(distance);

//
  if(distance<distanceMin && !vhcalligned) {
//if(true){

    delay(5000); // delay 10 second    
      // Set the current position to 0:
  stepperx.setCurrentPosition(0);
   steppery.setCurrentPosition(0);
 
  // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
  while(stepperx.currentPosition() != 225)
  {
    stepperx.setSpeed(50);
    stepperx.runSpeed();
  }
 
  delay(1000);

    while(steppery.currentPosition() != 225)
  {
    steppery.setSpeed(50);
    steppery.runSpeed();
  }
 
  delay(5000);
    stepperx.setCurrentPosition(0);
   steppery.setCurrentPosition(0);

    while(stepperx.currentPosition() != -225)
  {
    stepperx.setSpeed(-50);
    stepperx.runSpeed();
  }
 
  delay(1000);

    while(steppery.currentPosition() != -225)
  {
    steppery.setSpeed(-50);
    steppery.runSpeed();
  }
 
  delay(1000);

  vhcalligned = true;
    }

if(distance>distanceMin) {
  vhcalligned = false;
}
    
 
//  // Reset the position to 0:
//  stepperx.setCurrentPosition(0);
//  steppery.setCurrentPosition(0);
// 
//  // Run the motor backwards at 600 steps/second until the motor reaches -200 steps (1 revolution):
//  while(stepperx.currentPosition() != -200) 
//  {
//    stepperx.setSpeed(-600);
//    stepperx.runSpeed();
//  }
// 
//  delay(1000);
//  
//   while(steppery.currentPosition() != -200) 
//  {
//    steppery.setSpeed(-600);
//    steppery.runSpeed();
//  }
// 
//  delay(1000);
// 
//  // Reset the position to 0:
//  stepperx.setCurrentPosition(0);
//   steppery.setCurrentPosition(0);
// 
//  // Run the motor forward at 400 steps/second until the motor reaches 600 steps (3 revolutions):
//  while(stepperx.currentPosition() != 600)
//  {
//    stepperx.setSpeed(400);
//    stepperx.runSpeed();
//  }
// 
//  delay(3000);
//   while(steppery.currentPosition() != 600)
//  {
//    steppery.setSpeed(400);
//    steppery.runSpeed();
//  }
// 
//  delay(3000);
}
