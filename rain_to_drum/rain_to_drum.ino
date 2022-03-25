#include "volca_beats.h"

#define RAIN_SENS A0
#define KNOCK A3
int lastRain = 1024;

void setup() {
  //monitor
  Serial.begin(9600);

  // initialize beat
  Serial1.begin(31250);

}

void loop() {
  int rain = analogRead(RAIN_SENS);
  int knock = analogRead(KNOCK);
  Serial.println(knock);

  if ((rain < (lastRain - 100)) || (rain > (lastRain + 100))) {
    if (rain <= 300) {
      sendDrum(NOTE_ON, CL_HAT, 127);
    } else if (rain > 300 && rain <= 500) {
      sendDrum(NOTE_ON, CLAVES, 127);
    } else if (rain > 500 && rain <= 900) {
      sendDrum(NOTE_ON, CRASH, 127);
    }
    lastRain = rain;
  }

  if(knock > 30) {
    sendDrum(NOTE_ON, KICK, 127);
  }

  delay(100);  // delay between reads
}

void sendDrum(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}
