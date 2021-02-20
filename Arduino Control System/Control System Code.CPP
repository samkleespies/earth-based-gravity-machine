#include <Servo.h>;
const int kPinLed1 = 4;
const int parachuteDelay = 3000;                //Delay after RELEASE to open parachute tube
const int servoStop = parachuteDelay + 3000;    //Time when servos shut off to save battery
const int endAll = servoStop + 5000;            //Time of Motor shut off

Servo ESC1;     // create servo object to control the ESC
Servo ESC2;
Servo ESC3;
Servo ESC4;

void setup() {

//Motor Setup
  ESC1.attach(6,1000,2000);  // (pin, min pulse width, max pulse width in microseconds)
  ESC2.attach(9,1000,2000);
  ESC3.attach(10,1000,2000);
  ESC4.attach(11,1000,2000);

  ESC1.write(5);    // Send the signal to the ESC to activate
  ESC2.write(5);
  ESC3.write(5);
  ESC4.write(5);
  delay(7000);
  Serial.begin(9600);

  pinMode(kPinLed1,INPUT);
  digitalWrite(kPinLed1,HIGH);
}

int speedgood = 40;

void loop() {
long fallTime = millis();            //Will mark time of drop
long fallDuration = millis();        //Will update current time
long gap = fallDuration - fallTime;

  while(digitalRead(kPinLed1) == LOW){      // While LED1 is connected, program stays in this loop.
    fallTime = millis();                    //Both timers update while in this loop.
    fallDuration = millis();
  }


  while(gap < parachuteDelay){   //During the fall, but before parachuteDelay

//Timer
    fallDuration = millis();
    gap = fallDuration - fallTime;

//Motor Drive
    ESC1.write(speedgood);    // Send the signal to the ESC
    ESC2.write(speedgood);    // Send the signal to the ESC
    ESC3.write(speedgood);    // Send the signal to the ESC
    ESC4.write(speedgood);    // Send the signal to the ESC

//Motor Write
  speedgood = gap*0.07 + 40;

  }

  while(gap < servoStop){   //Once parachuteDelay is reached, but before servoStop
//Motor Stop
    ESC1.write(0);    // Send the signal to the ESC
    ESC2.write(0);    // Send the signal to the ESC
    ESC3.write(0);    // Send the signal to the ESC
    ESC4.write(0);    // Send the signal to the ESC


//Parachute Release
    /*servo.write(0);                    //New Servo positions, they move opposite because they...
    servo2.write(180);*/

//Timer
    gap = fallDuration - fallTime;
    fallDuration = millis();
  }

  while(gap < endAll){                 //After reaching servoStop
//Motor Detach
   ESC1.detach();
    ESC2.detach();
    ESC3.detach();
    ESC4.detach();

//Parachute Servo Detach
    servo.detach();
    servo2.detach();

//Timer
    gap = fallDuration - fallTime;
    fallDuration = millis();
  }

  while(gap >= endAll){                  //End of system

//Timer
    gap = fallDuration - fallTime;
    fallDuration = millis();
  }
}
