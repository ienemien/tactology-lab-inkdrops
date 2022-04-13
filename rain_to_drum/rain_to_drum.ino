#include "volca_beats.h"
#include <Adafruit_NeoPixel.h>

// nr of led, pin to send data
Adafruit_NeoPixel pixels(6, 7, NEO_GRB + NEO_KHZ800);

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

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  //monitor
  //Serial.begin(9600);

  // initialize beat
  delay(3000);
  Serial.begin(31250);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.show();

  delay(500);
}

void loop() {
  int rain_0 = analogRead(RAIN_0);
  int rain_1 = analogRead(RAIN_1);
  int rain_2 = analogRead(RAIN_2);
  int rain_3 = analogRead(RAIN_3);
  int rain_4 = analogRead(RAIN_4);
  int rain_5 = analogRead(RAIN_5);


  playRain(0, rain_0, lastRain0, CLAP);
  playRain(1, rain_1, lastRain1, CLAVES);
  playRain(2, rain_2, lastRain2, AGOGO);
  playRain(3, rain_3, lastRain3, KICK);
  playRain(4, rain_4, lastRain4, HI_TOM);
  playRain(5, rain_5, lastRain5, LO_TOM);

  delay(50);  // delay between reads
}

void sendDrum(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void playRain(int pin, int rain, int& lastRain, int note) {
  if (rain < lastRain && ((rain < (lastRain - 30)) || (rain > (lastRain + 30)))) {
    sendDrum(NOTE_ON, note, 127);
    delay(50);
    sendDrum(NOTE_OFF, note, 0);
    blinkLight(pin);
  }
  lastRain = rain;
}

void blinkLight(int lednr) {
  // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(lednr, pixels.Color(0, 0, 255));
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(50);
  pixels.clear();
  pixels.show();
}
