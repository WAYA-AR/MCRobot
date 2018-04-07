#include "MCWarningBluetooth.h"

using namespace std;

const unsigned long measurePeriode = 1000 ;

MCWarningBluetooth::MCWarningBluetooth() {
}
/*
  MCWarningBluetooth::MCWarningBluetooth(int serialBaud,
                                       int _pinWarning,
                                       int _pinTrig,
                                       int _pinEcho) {
  bluetooth = new MCBluetooth(serialBaud);
  init(_pinWarning,
       _pinTrig,
       _pinEcho);
  }
*/
MCWarningBluetooth::MCWarningBluetooth(MCBluetooth *_bluetooth,
                                       int _pinWarning,
                                       int _pinTrig,
                                       int _pinEcho) {
  bluetooth = _bluetooth;
  init(_pinWarning,
       _pinTrig,
       _pinEcho);
}

void MCWarningBluetooth::init(
  int _pinWarning,
  int _pinTrig,
  int _pinEcho) {
  pinWarning = _pinWarning;
  pinTrig = _pinTrig;
  pinEcho = _pinEcho;

  pinMode(pinWarning, OUTPUT);

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  enableWarning(false);

  lastDistanceMeasure = millis();
}

bool MCWarningBluetooth::readAndProcess() {

  if ((*bluetooth).getInChar() == '$') {
    String warningString = String((*bluetooth).getInData());
    if  (warningString.equals("WARN0$")) {
      enableWarning(false);
    } else if (warningString.equals("WARN1$")) {
      enableWarning(true);
    }
    (*bluetooth).clearData();
    return true;
  }
  return false;
}



void MCWarningBluetooth::enableWarning(bool isOn) {
  if (isOn) {
    //    tone(pinWarning, 87);
    digitalWrite(pinWarning, 1);
  } else {
    //    noTone(pinWarning);
    digitalWrite(pinWarning, 0);
  }
}

int MCWarningBluetooth::measureDistance() {
  // Clears the trigPin
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(10);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(pinEcho, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //  Serial.print("Distance: ");
  //  Serial.println(distance);
  return distance;
}


void MCWarningBluetooth::measureAndSend() {
  if (millis() - lastDistanceMeasure > measurePeriode) {
    lastDistanceMeasure = millis();
    int dist = measureDistance();
    String msg = "DIS" + String(dist) + "$";
    (*bluetooth).writeln(msg);
  }
}

