
#include "MCBluetooth.h"
#include "MCMotorBluetooth.h"
#include "MCWarningBluetooth.h"

MCBluetooth bluetooth;
MCMotorBluetooth motorBluetooth;
MCWarningBluetooth warningBluetooth;


int pin1Moteur1 = 12; //pin de commande moteur 1
int pin2Moteur1 = 8; // pin de commande moteur 1
int pinPMoteur1 = 11; // pin PWM moteur 1
int pin1Moteur2 = 2; // pin de commande moteur 2
int pin2Moteur2 = 4; // pin de commande moteur 2
int pinPMoteur2 = 5; // pin PWM moteur 2 

int pinWarning = 6;    // pin Warning

int pinTrig  = 9; // Broche TRIGGER
int pinEcho  = 10;    // Broche ECHO


void setup() {

  bluetooth = MCBluetooth::MCBluetooth(9600);
  
  motorBluetooth = MCMotorBluetooth::MCMotorBluetooth(&bluetooth,
                   pin1Moteur1,
                   pin2Moteur1,
                   pinPMoteur1,
                   pin1Moteur2,
                   pin2Moteur2,
                   pinPMoteur2);
                   
  warningBluetooth = MCWarningBluetooth::MCWarningBluetooth(&bluetooth,
                     pinWarning,
                     pinTrig,
                     pinEcho);
}

void readAndProcess() {
  while (bluetooth.read()) // Don't read unless
    // there you know there is data
  {


    if (motorBluetooth.readAndProcess()) {
      return;
    }

    if (warningBluetooth.readAndProcess()) {
      return;
    }

  }
}


void loop() {
  readAndProcess();
  warningBluetooth.measureAndSend();
}

