This Arduino code controls a round-robot with two wheels and an IR distance sensor mounted on a servo motor.
The robot will travel forward until it detects an obstacle or lack of floor. Then it will stop, assess which is the best route to take, it will pivot and continue traveling.

The robot is controlled by an Arduino Uno, using the following ports:
- Two PWM ports to control each DC motor on the wheels
- One PWM port to control the servo motor
- One analog input port to acquire the data sent by the IR sensor

Suggested material:
- Chasis and wheels DC motors: https://www.adafruit.com/products/3216
- Servo motor: https://www.adafruit.com/products/1143
- IR distance sensor: https://www.adafruit.com/products/164
- For autonomy, two LiPo batteries can be used: https://www.adafruit.com/products/1578


