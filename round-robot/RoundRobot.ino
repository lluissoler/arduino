int state = 0; // state of the machine

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

#include <Servo.h> // Servo library
int servoPin = 9; // Pin where the servo motor is connected
Servo servo; // create servo object
int angle = 0;   // servo position in degrees
int frontAngle = 0; // defines the angle of the servo motor when the robot is looking forward

#include <SoftwareSerial.h> // virtual serial for Bluetooth and GPS
static const uint32_t BTBaud = 9600;
SoftwareSerial BT(12, 13); // Bluetooth: TX to 12, RX to 13, Vcc to 5V, GND to GND

int motor1Pin = 3; // right motor pin
int motor2Pin = 5; // left motor pin
int motorsSpeed = 185; // PWM value for wheels (DC motors are 3-6 VDC)
int turnDirection = 0; // -1: left, 1: right

bool mainStart = true; // main ON/OFF switch set by the user
int minObjectDistance = 350; // sensor value when robot will understand there is an obstacle
int maxObjectDistance = 50; // sensor value when robot will understand there is no floor

// Setup loop
void setup() {
  
  // Open Serial port (debugging)
  Serial.begin(9600);  // Serial port to connect to the CPU
  Serial.println("Starting Robot...");

  // Open Bluetooth port
  BT.begin(BTBaud);
  BT.println("Connected! Send ? for help");

  // Define PWM ports for DC motors
  pinMode(motor1Pin, OUTPUT); // define pin for motor 1
  pinMode(motor2Pin, OUTPUT); // define pin for motor 2
}

// Main loop
void loop() {
  int distance = 0;
  int sweepAngle;
  int distArray[5];
  int sampleD = 0;
  float leftDist;
  float rightDist;

  // Check for user inputs (Serial port)
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if (incomingByte == 48) {
      mainStart = false;
      state = 0;
    } else if (incomingByte == 49) {
      mainStart = true;
    }
    Serial.println(incomingByte);
  }

  // Check for user inputs (BT port)


  switch (state) {
    case -1: // Idle, do nothing, wait until user asks to move
      distance = ReadDistance(-1000);
      Serial.print(state); Serial.print(": "); Serial.println(distance);
      
      if (mainStart == true) {
        state = 1; // go to travel mode
      }
      break;

    case 0: // Stop motors and go idle
      analogWrite(motor1Pin, 0);
      analogWrite(motor2Pin, 0);
      moveServoMotor(frontAngle);
      servo.detach(); // Start servo motor
      Serial.println(state);
      state = -1;
      delay(250);
      break;

    case 1: // travel
      if (mainStart == true) {
        servo.attach(servoPin); // Start servo motor
        distance = ReadDistance(frontAngle);
        Serial.print(state); Serial.print(": "); Serial.println(distance);
        if (distance < minObjectDistance && distance > maxObjectDistance) {
          // no obstacle detected to the front, move forward
          analogWrite(motor1Pin, motorsSpeed);
          analogWrite(motor2Pin, motorsSpeed);
        } else {
          // obstacle detected
          state = 2;
        }
      } else {
        state = 0;
      }
      break;

    case 2: // stop and sweep for obstacles
      analogWrite(motor1Pin, 0);
      analogWrite(motor2Pin, 0);

      // Scan direction and put distances in an array
      sampleD = 0;
      for (sweepAngle = -90; sweepAngle <= 90; sweepAngle = sweepAngle + 45) {
        distance = ReadDistance(sweepAngle);
        distArray[sampleD] = distance;
        sampleD = sampleD + 1;
        Serial.print(state); Serial.print(": At "); Serial.print(sweepAngle); Serial.print("deg, "); Serial.println(distance);
        delay(500);
      }

      leftDist = 0.5 * (distArray[3] + distArray[4]);
      rightDist = 0.5 * (distArray[0] + distArray[1]);

      if (leftDist <= rightDist) {
        turnDirection = -1;
      } else {
        turnDirection = 1;
      }

      state = 3;
      break;

    case 3: // turn

      if (turnDirection < 0){ // turn left
        analogWrite(motor1Pin, motorsSpeed);
        analogWrite(motor2Pin, 0);
      } else if (turnDirection > 0) { // turn right
        analogWrite(motor1Pin, 0);
        analogWrite(motor2Pin, motorsSpeed);
      } 

      delay(500);
      analogWrite(motor1Pin, 0);
      analogWrite(motor2Pin, 0);
      
      Serial.println(state);
      state = 1; // go to travel. In case there is still an obstacle, it will go back to the sweep
      break;

  } // end of state switch

  delay(50);

} // end of main loop

// Get value from IR distance sensor at the specific angle. Return the average of nSamples
int ReadDistance(int angle) {
  int nSamples = 5;
  int sVal = 0;
  int i;

  if (angle != -1000) {
    moveServoMotor(angle);
  }

  for (i = 0; i < nSamples; i++) {
    sVal = sVal + analogRead(sensorPin);
  }
  sVal = sVal / nSamples; // average analog reading
  return sVal;

}

// Move the servo motor to the desired angle
void moveServoMotor(int angle) {
  angle = angle + 90; // this is to convert from servo to robot coordinate reference
  servo.write(angle);
  delay(250);
}


// Bluetooth data
void readBTPort() {
  char BTmsg = '\0';
  
  BT.listen();
  while (BT.available() > 0) {
    // if text arrived in from BT serial...
    BTmsg = (BT.read());
  }
  
  if (BTmsg == '1') {
      mainStart = true;
  } else if (BTmsg == '0') {
      mainStart = false;
      state = 0;
  } else if (BTmsg == '?') {
      BT.println("Send '1' to start robot");
      BT.println("Send '0' to stop robot");
  }
}
