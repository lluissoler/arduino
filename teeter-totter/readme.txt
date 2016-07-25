This folder contains different codes to control a teeter-totter that has a small propeller on each end. It also has an accelerometer on its axis to sense the current angle.

Material:
- The accelerometer used is the MMA8451, and you can find its library in https://github.com/adafruit/Adafruit_MMA8451_Library
- the motors are two 3VDC brush motors with a propeller attached to their shafts. Both are from http://www.microflight.com/

Programs:
- follow_sensor: simple program to independently control the two DC by following the readings from the sensor (the sensor here is not attached to the teeter-totter). It is an open-loop control to show how readings from sensor are transformed to horizontal angle and how the Arduino sends commands to the motors
- teeter-totter: this program gets the actual angle of the teeter-totter through the accelerometer and generates the outputs of the motor in order to stabilize it in a reference angle entered by the user.
