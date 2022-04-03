#include "volca_beats.h"
#include <Adafruit_NeoPixel.h>

// nr of led, pin to send data
Adafruit_NeoPixel pixels(1, 7, NEO_GRB + NEO_KHZ800);

#define RAIN_0 A0
#define RAIN_1 A1
#define RAIN_2 A2
#define RAIN_3 A3
#define RAIN_4 A4
#define RAIN_5 A5
int lastRain0 = 1024;
int lastRain1 = 1024;
int lastRain2 = 1024;
int lastRain3 = 1024;
int lastRain4 = 1024;
int lastRain5 = 1024;

#define LED_1 1

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  //monitor
  Serial.begin(9600);

  // initialize beat
  Serial1.begin(31250);

  //pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  //pixels.show(); // turn off all pixels asap
}

void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'
  //pixels.show();
  
  //todo: optimize code
  int rain_0 = analogRead(RAIN_0);
  int rain_1 = analogRead(RAIN_1);
  int rain_2 = analogRead(RAIN_2);
  int rain_3 = analogRead(RAIN_3);
  int rain_4 = analogRead(RAIN_4);
  int rain_5 = analogRead(RAIN_5);

  printValue(0, rain_0, lastRain0);
  playRain(rain_0, lastRain0, CLAP);
  lastRain0 = rain_0;

  printValue(1, rain_1, lastRain1);
  playRain(rain_1, lastRain1, CLAVES);
  lastRain1 = rain_1;

  printValue(2, rain_2, lastRain2);
  playRain(rain_2, lastRain2, AGOGO);
  lastRain2 = rain_2;

  printValue(3, rain_3, lastRain3);
  playRain(rain_3, lastRain3, CRASH);
  lastRain3 = rain_3;

  printValue(4, rain_4, lastRain4);
  playRain(rain_4, lastRain4, HI_TOM);
  lastRain4 = rain_4;

  printValue(5, rain_5, lastRain5);
  playRain(rain_5, lastRain5, OP_HAT);
  lastRain5 = rain_5;

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

void playRain(int rain, int lastRain, int note) {
  if ((rain < (lastRain - 50)) || (rain > (lastRain + 50))) {
      sendDrum(NOTE_ON, note, 127);
      sendDrum(NOTE_OFF, note, 127);
      //blinkLight(0);
  }
}

void blinkLight(int lednr) {
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(lednr, pixels.Color(0, 0, 230));

    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(50);
    pixels.clear();
    pixels.show();
}
