// WIRING I2C https://www.instructables.com/Arduino-I2C-and-Multiple-Slaves/

#include <Wire.h>

#define FPS 25

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}

unsigned int hours = 0;
unsigned int minutes = 0;
unsigned int seconds = 0;
unsigned int frames = 0;

void loop()
{
  log();
  String timecode = String(padNumber(hours) + padNumber(minutes) + padNumber(seconds) + padNumber(frames));
  Wire.beginTransmission(4);
  Wire.write(timecode.c_str());
  Wire.endTransmission();
  Wire.beginTransmission(5);
  Wire.write(timecode.c_str());
  Wire.endTransmission();

  delay(1000 / FPS);
  tick();
}

void log() {
  Serial.print(hours,DEC);  
  printDigits(minutes);
  printDigits(seconds);
  printDigits(frames);
  Serial.println();  
}

String padNumber(int number) {
  if (number < 10) {
    return String("0") + number;
  }

  return String(number, DEC);
}

void printDigits(byte digits){
  // utility function for digital clock display: prints colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits,DEC);   
}

void tick() {
  if (frames == FPS) {
    seconds++;
    frames = 0;
  }

  if (seconds == 60) {
    minutes++;
    seconds = 0;
  }

  if (minutes == 60) {
    hours++;
    minutes = 0;
  }

  if (hours == 24) {
    hours = 0;
  }

  frames++;
}