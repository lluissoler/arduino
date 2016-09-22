RoundRobot.ino controls a round-robot with two wheels and an IR distance sensor mounted on a servo motor.
The robot will travel forward until it detects an obstacle or lack of floor. Then it will stop, assess which is the best route to take, it will pivot and continue traveling.
To control it (start/stop), a Bluetooth can also be added. By using any Bluetooth App (I use Bluetooth Terminal for Android), you can send messages to the board: the current code is set so that if you send a '1' it will start and it will stop by sending a '0'.

The robot is controlled by an Arduino Uno, using the following ports:
- Two PWM ports to control each DC motor on the wheels
- One PWM port to control the servo motor
- One analog input port to acquire the data sent by the IR sensor
- Two digital ports used as virtual serial port (using SoftwareSerial library) to communicate the board with a Bluetooth device

Suggested material:
- Chasis and wheels DC motors: https://www.adafruit.com/products/3216
- Servo motor: https://www.adafruit.com/products/1143
- IR distance sensor: https://www.adafruit.com/products/164
- Bluetooth TX/RX: https://www.amazon.com/gp/product/B00L08GA4Q
- For autonomy, two LiPo batteries can be used: https://www.adafruit.com/products/1578


