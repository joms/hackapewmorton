// https://www.tme.eu/Document/c85fc6fed6cec71bef39decf36c8c4a0/CA56-12SURKWA.pdf
// https://www.circuitbasics.com/arduino-7-segment-display-tutorial/
// https://github.com/DeanIsMe/SevSeg?tab=readme-ov-file

#include "SevSeg.h"
#include <Wire.h>

SevSeg leftSeg;
SevSeg rightSeg;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  
  byte leftSegDigitPins[] = {40, 41, 42, 43};
  byte leftSegPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
  byte rightSegDigitPins[] = {44, 45, 46, 47};
  byte rightSegPins[] = {30, 31, 32, 33, 34, 35, 36, 37};
  byte numDigits = 4;
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  leftSeg.begin(hardwareConfig, numDigits, leftSegDigitPins, leftSegPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  rightSeg.begin(hardwareConfig, numDigits, rightSegDigitPins, rightSegPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
}

String hours = "--";
String minutes = "--";
String seconds = "--";
String frames = "--";

void loop() {
  drawSevSeGCounter();
}

int counter = 0;
void drawSevSeGCounter() {
  counter++;
  if (counter % 500 == 0) {
    Serial.println(String(hours+"."+minutes+"."+seconds+"."+frames));
  }

  leftSeg.setChars(String(hours+"."+minutes+".").c_str());
  leftSeg.refreshDisplay();
  rightSeg.setChars(String(seconds+"."+frames).c_str());
  rightSeg.refreshDisplay();
}

void receiveEvent(int howMany)
{
  String str = "";
  while(Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    str += c;
  }

  hours = str.substring(0, 2);
  minutes = str.substring(2, 4);
  seconds = str.substring(4, 6);
  frames = str.substring(6, 8);
}