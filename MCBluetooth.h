#ifndef MCBluetooth_h
#define MCBluetooth_h

#include "Arduino.h"

class MCBluetooth
{
  public:
    MCBluetooth();
    MCBluetooth(int serialBaud/*9600*/);
    bool read();
    void clearData();
    void write(String msg);
    void writeln(String msg);

    String getInData();
    char getInChar();
    byte getIndex();
  private:
    char inData[20]; // Allocate some space for the string
    char inChar; // Where to store the character read
    byte index; // Index into array; where to store the character
};

#endif

