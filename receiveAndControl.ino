#include <VirtualWire.h> //Add VirtualWire RF virtual library
#include <Servo.h> //Add Servo library for ESCs
int potVal;
int xVal;
int yVal;
int UR;
int UL;
int BR;
int BL;

//Declare 4 Motors (U = Upper, B = Back, R = Right, L = Left)
Servo DUR;
Servo DUL;
Servo DBR;
Servo DBL;

//Declare variables for up, down, left, right, forward backward directions, including variables that can store values from previous program runs


//Declare struct called package, with x, y, and potentiometer variables
struct package {
  unsigned char potVal;
  unsigned char xVal;
  unsigned char yVal;
};

//Declare a new type of variable in the form of a struct named package, and name it Package
typedef struct package Package;

//Declare a name for your variable with the identity "Package" (same thing as int led;)
Package data;

void setup() {
    vw_set_rx_pin(7);
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
    
    //Attach the motors on PWM ports
    DUR.attach(3);
    delay(1); //Figure out ESC delay and "write" values in a way such that the Arduino pairs with the ESCs (armed)
    DUR.write(40);
    
    DUL.attach(5);
    delay(1);
    DUL.write(40);
    
    DBR.attach(6);
    delay(1);
    DBR.write(40);
    
    DBL.attach(9);
    delay(1);
    DBL.write(40);
}

void loop() {
    uint8_t buf[sizeof(data)]; //Declare an 8 bit unsigned character array "buf" and give it a length the size of our recieved data
    uint8_t buflen = sizeof(data); //Declare a variable buflen, equal to the size of the received data

    if (vw_have_message()) { //Have we received a message?
	vw_get_message (buf, &buflen); //Get the message
        memcpy (&data, &buf, buflen); //Copy it to the data struct

        potVal = map (data.potVal, 0, 255, 0, 120);
        xVal = map (data.xVal, 0, 255, -90, 90);
        yVal = map (data.yVal, 0, 255, -90, 90);
        
        xVal = xVal/6;
        yVal = yVal/6;

        UR = potVal+xVal-yVal;
        UL = potVal-xVal-yVal;
        BR = potVal+xVal+yVal;
        BL = potVal-xVal+yVal;
        if (UR < 0){
          UR = 0;
        }
        if (UL < 0) {
          UL = 0;
        }
        if (BR < 0) {
          BR = 0;
        }
        if (BL < 0) {
          BL = 0;
        }
        
        DUR.write (UR);
        DUL.write (UL);
        DBR.write (BR);
        DBL.write (BR);
    }
    delay (200);
}
