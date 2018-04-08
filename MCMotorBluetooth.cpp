#include "MCMotorBluetooth.h"

using namespace std;


MCMotorBluetooth::MCMotorBluetooth() {
}
/*
MCMotorBluetooth::MCMotorBluetooth(int serialBaud,
                                   int _pin1Moteur1,
                                   int _pin2Moteur1,
                                   int _pinPMoteur1,
                                   int _pin1Moteur2,
                                   int _pin2Moteur2,
                                   int _pinPMoteur2) {
  bluetooth = new MCBluetooth(serialBaud);
  init(_pin1Moteur1,
       _pin2Moteur1,
       _pinPMoteur1,
       _pin1Moteur2,
       _pin2Moteur2,
       _pinPMoteur2);
}
*/

MCMotorBluetooth::MCMotorBluetooth(MCBluetooth *_bluetooth,
                                   int _pin1Moteur1,
                                   int _pin2Moteur1,
                                   int _pinPMoteur1,
                                   int _pin1Moteur2,
                                   int _pin2Moteur2,
                                   int _pinPMoteur2) {
  bluetooth = _bluetooth;
  init(_pin1Moteur1,
       _pin2Moteur1,
       _pinPMoteur1,
       _pin1Moteur2,
       _pin2Moteur2,
       _pinPMoteur2);
}

void MCMotorBluetooth::init(
  int _pin1Moteur1,
  int _pin2Moteur1,
  int _pinPMoteur1,
  int _pin1Moteur2,
  int _pin2Moteur2,
  int _pinPMoteur2) {
  pin1Moteur1 = _pin1Moteur1;
  pin2Moteur1 = _pin2Moteur1;
  pinPMoteur1 = _pinPMoteur1;
  pin1Moteur2 = _pin1Moteur2;
  pin2Moteur2 = _pin2Moteur2;
  pinPMoteur2 = _pinPMoteur2;
  pinMode(pin1Moteur1, OUTPUT);
  pinMode(pin2Moteur1, OUTPUT);
  pinMode(pinPMoteur1, OUTPUT);
  pinMode(pin1Moteur2, OUTPUT);
  pinMode(pin2Moteur2, OUTPUT);
  pinMode(pinPMoteur2, OUTPUT);
}

bool MCMotorBluetooth::readAndProcess() {
  if ((*bluetooth).getInChar() == ']') {
    processMotorString();
    (*bluetooth).clearData();
    return true;
  }

  return false;
}


void MCMotorBluetooth::processMotorString() {

  String is1OnString = "0";
  String percentage1String = "0";
  String is2OnString = "0";
  String percentage2String = "0";


  String stringData = String((*bluetooth).getInData());
  is1OnString = stringData.substring(1, 2);
  percentage1String = stringData.substring(3, 6);
  is2OnString = stringData.substring(7, 8);
  percentage2String = stringData.substring(9, 12);



  int is1On = is1OnString.toInt();
  if (is1On == 2) {
    is1On = -1;
  }
  int percentage1 = percentage1String.toInt();
  int is2On = is2OnString.toInt();
  if (is2On == 2) {
    is2On = -1;
  }
  int percentage2 = percentage2String.toInt();

  /*Serial.print("receivedString=[");
    Serial.print(is1On);
    Serial.print(":");
    Serial.print(percentage1);
    Serial.print(":");
    Serial.print(is2On);
    Serial.print(":");
    Serial.print(percentage2);
    Serial.println("]");*/
  actionMoteur(1, is1On, percentage1); //moteur 1 100% puissance sens 1
  actionMoteur(2, is2On, percentage2); //arrêt moteur 2
}
void MCMotorBluetooth::actionMoteur(int moteur, int sens, int pourcentage) {
  int pin1, etat1, pin2, etat2, pinP, puissance; //variable de la fonction
  //test numéro du moteur
  if (moteur == 1) {
    pin1 = pin1Moteur1;
    pin2 = pin2Moteur1;
    pinP = pinPMoteur1;
  }
  else {
    pin1 = pin1Moteur2;
    pin2 = pin2Moteur2;
    pinP = pinPMoteur2;
  }
  //test sens du moteur 1,-1 (sens contrainre) ou tout autre valeur (stoppe le moteur)
  if (sens == 1) {
    etat1 = 1;
    etat2 = 0;
  } else if (sens == -1) {
    etat1 = 0;
    etat2 = 1;
  } else {
    etat1 = 0;
    etat2 = 0;
  }
  puissance = map(pourcentage, 0, 100, 0, 255);
  analogWrite(pinP, puissance);
  digitalWrite(pin1, etat1);
  digitalWrite(pin2, etat2);
  
  Serial.print("Moteur : ");
  Serial.print(moteur);
  if (sens == -1 || sens == 1) {
    Serial.print(" sens : ");
    Serial.print(sens);
  }
  else {
    Serial.print(" ! stop ! ");
  }
  Serial.print(" puissance : ");
  Serial.println(pourcentage);
}
