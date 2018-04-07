#ifndef MCMotorBluetooth_h
#define MCMotorBluetooth_h

#include "Arduino.h"
#include "MCBluetooth.h"

class MCMotorBluetooth {
  public:
    MCMotorBluetooth();
    MCMotorBluetooth(MCBluetooth *_bluetooth,
                     int _pin1Moteur1,
                     int _pin2Moteur1,
                     int _pinPMoteur1,
                     int _pin1Moteur2,
                     int _pin2Moteur2,
                     int _pinPMoteur2);

    /*MCMotorBluetooth(int serialBaud,
                     int _pin1Moteur1,
                     int _pin2Moteur1,
                     int _pinPMoteur1,
                     int _pin1Moteur2,
                     int _pin2Moteur2,
                     int _pinPMoteur2);*/
    bool readAndProcess();

  private:
    int pin1Moteur1; //pin de commande moteur 1
    int pin2Moteur1; // pin de commande moteur 1
    int pinPMoteur1; // pin PWM moteur 1
    int pin1Moteur2; // pin de commande moteur 2
    int pin2Moteur2; // pin de commande moteur 2
    int pinPMoteur2; // pin PWM moteur 2
    MCBluetooth *bluetooth;

    void MCMotorBluetooth::init(
      int _pin1Moteur1,
      int _pin2Moteur1,
      int _pinPMoteur1,
      int _pin1Moteur2,
      int _pin2Moteur2,
      int _pinPMoteur2);

    void actionMoteur(int moteur, int sens, int pourcentage);
    void processMotorString();
};

#endif

