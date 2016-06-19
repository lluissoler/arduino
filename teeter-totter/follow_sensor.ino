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

 
void setup() 
{ 
  // Motors pins
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
 
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
} 
 
void loop() 
{ 

  // Read the accelerometer
  // Read the 'raw' data in 14-bit counts
  mma.read();
  
  // Get a new sensor event
  sensors_event_t event; 
  mma.getEvent(&event);

  double angle = atan2(mma.x,mma.z)*180/3.1415;

  // Display the results (acceleration is measured in m/s^2)
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  // Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.print("m/s^2 ");
  Serial.print("\t Angle: \t"); Serial.println(angle);


  // Use the angle obtained from the sensor to produce an output
  int speed1 = (int) -2.222*angle + 100;
  int speed2 = (int)  2.222*angle + 100;
   
  if (speed1 >= 0 && speed1 <= 255)
  {
    analogWrite(motor1Pin, speed1);
  }
  if (speed2 >= 0 && speed1 <= 255)
  {
    analogWrite(motor2Pin, speed2);
  }
  Serial.println("Speed 1: " + String(speed1) + "; Speed 2: " + String(speed2));


  
  delay(1000);
  
} 
