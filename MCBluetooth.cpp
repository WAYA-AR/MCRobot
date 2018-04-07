#include "Arduino.h"
#include "MCBluetooth.h"

MCBluetooth::MCBluetooth() {
  MCBluetooth(9600);
}

MCBluetooth::MCBluetooth(int serialBaud) {
  Serial.begin(serialBaud);
  inChar = -1; // Where to store the character read
  index = 0; // Index into array; where to store the character
}

bool MCBluetooth::read() {
  if (Serial.available() > 0) // Don't read unless there you know there is data
  {
    if (index < 19) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    }

    if (inChar == '#') {
      clearData();
    }

    return true;

  }
  return false;
}


String MCBluetooth::getInData() {
  return String(inData);
}
char MCBluetooth::getInChar() {
  return inChar;

}
byte MCBluetooth::getIndex() {
  return index;
}

void MCBluetooth::clearData() {
  for (int i = 0; i < 19; i++) {
    inData[i] = 0;
  }
  index = 0;
}


void MCBluetooth::write(String msg) {
  Serial.print(msg);
}

void MCBluetooth::writeln(String msg) {
  Serial.println(msg);
}
