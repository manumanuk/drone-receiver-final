# drone-receiver-final
Receiver code for Arduino-programmed drone. Consists of an RF (radio module) receiver which takes in serial data from the transmitter and converts it into commands for each of the four motors.

Directional commands are as follows:

* To go right, the top right and bottom right motors of the quadcopter are turned down. The other two are turned up.
* To go left, the top left and bottom left motors of the quadcopter are turned down. The other two are turned up.
* To go back, the bottom right and bottom left motors of the quadcopter are turned down. The other two are turned up.
* To go forward, the top right and top left motors of the quadcopter are turned down. The other two are turned up.
