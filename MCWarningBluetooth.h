#ifndef MCWarningBluetooth_h
#define MCWarningBluetooth_h

#include "Arduino.h"
#include "MCBluetooth.h"

class MCWarningBluetooth {
  public:
    MCWarningBluetooth();
    MCWarningBluetooth(MCBluetooth *_bluetooth,
                       int _pinWarning,
                       int _pinTrig,
                       int _pinEcho);
/*
    MCWarningBluetooth(int serialBaud,
                     int _pinWarning,
                     int _pinTrig,
                     int _pinEcho);*/
    bool readAndProcess();
    void measureAndSend();

  private:
    int pinWarning; //pin de commande moteur 1
    int pinTrig; // pin de commande moteur 1
    int pinEcho;
    MCBluetooth *bluetooth;
    unsigned long lastDistanceMeasure = 0 ;

    void init(
      int _pinWarning,
      int _pinTrig,
      int _pinEcho);

    void enableWarning(bool isOn);
    int measureDistance();
};

#endif

