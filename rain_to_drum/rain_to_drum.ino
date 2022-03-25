#include "volca_beats.h"

#define RAIN_0 A0
#define RAIN_1 A1
#define RAIN_2 A2
int lastRain0 = 1024;
int lastRain1 = 1024;
int lastRain2 = 1024;

void setup() {
  //monitor
  Serial.begin(9600);

  // initialize beat
  Serial1.begin(31250);

}

void loop() {
  int rain_0 = analogRead(RAIN_0);
  int rain_1 = analogRead(RAIN_1);
  int rain_2 = analogRead(RAIN_2);

  printValue(0, rain_0, lastRain0);
  playRain(rain_0, lastRain0);
  lastRain0 = rain_0;

  printValue(1, rain_1, lastRain1);
  playRain(rain_1, lastRain1);
  lastRain1 = rain_1;

  printValue(2, rain_2, lastRain2);
  playRain(rain_2, lastRain2);
  lastRain2 = rain_2;

  delay(50);  // delay between reads
}

void printValue(int pinNr, int rain, int lastRain) {
  char buffer[40];
  sprintf(buffer, "%d: %d last value: %d", pinNr, rain, lastRain);
  Serial.println(buffer);
}

void sendDrum(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}

void playRain(int rain, int lastRain) {
  if ((rain < (lastRain - 50)) || (rain > (lastRain + 50))) {
    if (rain <= 300) {
      sendDrum(NOTE_ON, CL_HAT, 127);
    } else if (rain > 300 && rain <= 500) {
      sendDrum(NOTE_ON, CLAVES, 127);
    } else if (rain > 500 && rain <= 900) {
      sendDrum(NOTE_ON, CRASH, 127);
    }
  }
}
