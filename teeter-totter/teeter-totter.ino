// Pins used for the DC motors
int motor1Pin = 9;
int motor2Pin = 11;

int speed1;
int speed2;

// Accelerometer libraries
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
Adafruit_MMA8451 mma = Adafruit_MMA8451();

// Readings
const int numReadings = 50;
double readings[numReadings];
int readIndex = 0; // index of the current reading
double totalReadings = 0; // running total
double averageAngle = 0; // average of the current readings array



void setup() 
{ 
  // Motors pins
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);

  // Initialize values
  int speed1 = 100;
  int speed2 = 100;
  int angleRef = 0;
  
  // Start serial
  Serial.begin(9600);
  while (! Serial);

  // Start accelerometer
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
  Serial.println("Speed 0 to 255 (motor1,motor2)");

} // end of setup
 
void loop() 
{ 

  // Average values of the sensor
  totalReadings = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    // Read the accelerometer, Read the 'raw' data in 14-bit counts
    mma.read();
    
    // Get a new sensor event
    sensors_event_t event; 
    mma.getEvent(&event);

    // Calculate the horizontal angle
    double angle = atan2(mma.x,mma.z)*180/3.1415;

    readings[thisReading] = angle;
    totalReadings = totalReadings + readings[thisReading];
    delay(10);
  }
  averageAngle = totalReadings / numReadings;


  // When serial input is available, read the reference entered by the user
  if (Serial.available())
  {
    
    // Parse the inputs into the 2 speeds of the motors
    String serialRead = Serial.readString();
    int angleRef = Serial.read();
    
  }

  // Controller: increase decrease output to achieve reference angle
  float angleDiff = refAngle - refAngle;
  if (angleDiff > 3) {
    speed1 = speed1 + 5;
    speed2 = speed2 - 5;
  }
  if (angleDiff < -3) {
    speed1 = speed1 - 5;
    speed2 = speed2 + 5;
  }

  // Saturation values
  if (speed1 < 0) {speed1 = 0}
  if (speed1 > 225) {speed1 = 225}
  if (speed2 < 0) {speed2 = 0}
  if (speed2 > 225) {speed2 = 225}
  
  analogWrite(motor1Pin, speed1);
  analogWrite(motor2Pin, speed2);


  // Print the measured angle
  Serial.print("\t Actual Angle: \t"); Serial.print(averageAngle); Serial.println(" deg.");

  // Print the reference angle
  Serial.print("\t Ref. Angle: \t"); Serial.print(angleRef); Serial.println(" deg.");

  // Print the motor outputs
  Serial.print("\t Speeds: \t"); Serial.print(speed1); Serial.print("\t , \t"); Serial.println(speed2);
  Serial.println();

  
  delay(50);
} // end of loop
