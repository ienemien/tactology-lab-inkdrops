# tactology-lab-inkdrops

This is a project to play the Korg Volca Beats with water-/inkdrops through an Arduino that sends midi messages to the Volca, for each rain sensor there is also a neopixels that lights up when the sensor is played.

## What you need

- An Arduino Mega, although an Uno might also suffice
- A 9V power adapter for the Arduino
- A Korg Volca Beats, though ofcourse you can also try other MIDI devices, but you might need to change which note is sent. A lot of MIDI devices have a MIDI implementation chart.
- A power adapter or batteries for the Korg
- A breadboard
- 6 raindrop sensors, I got mine from  TinyTronics: https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor + 18 female to male jumper wires (or just normal stranded wires if you solder them)
- A 5 pole DIN connector bus that can be put into a breadboard
- 2 220 ohm resistors
- A male to male MIDI cable
- A 6 neopixel strip or 6 individual leds, like this one: https://www.benselectronics.nl/ws2812-rgb-breakout.html + wires to connect them and solder + a soldering station

## How to connect everything

- For connecting the MIDI bus, follow this guide: https://www.arduino.cc/en/pmwiki.php?n=Tutorial/Midi
- Connect a wire from the 5V output of the Arduino to the red strip on the breadboard and a wire from the ground to the blue strip on the breadboard
- Connect the raindrops sensors to the + and - of their breakout boards (it doesn't matter which way this is done, since resistors don't have a direction)
- Connect the 5V connectors of the breakout boards of the rainsensors to one of the connections on the red line of the breadboard
- Do the same for ground to the blue line on the breadboard
- Connect the analog out pin of each sensor to the analog inputs of the Arduino (input A0 to A5)
- Connect the 5V pin of the first neopixel to the 3.3V pin of the Arduino, connecting it to the 5V pin can cause problems, read more here: https://blog.adafruit.com/2016/10/28/tips-for-troubleshooting-neopixel-glitches/
- Connect the ground pin of the first neopixel to the ground pin of the Arduino and the 'data in'(din) pin to the digital pin 7 (if you want to change this, change the second parameter of this line: Adafruit_NeoPixel pixels(6, 7, NEO_GRB + NEO_KHZ800);)
- Connect the 5V of the first pixel to the 5V of the second one, the ground to the ground and the dout of the first pixel to the din of the second pixel, repeat this for the following pixels (or skip if you use a strip)
- Connect the MIDI cable to the DIN bus and the Korg

## Testing the setup
- Check if the left green light for each sensor is on  consistently
- Use a bottle of water or your fingers with water on them to test each sensor and see if a sound is played
- Also test if a neopixel lights up for each sensor, the first neopixel should light up for the sensor connected to A0 the last pixel for sensor A5

## Troubleshooting
- If no sound is played at all and no light is blinking, check if all 5V and ground pins are connected correctly and are not switched (you will also see the sea green light blinking repeatedly if they are not connected correctly)
- If you put water on the sensor, the second green light of the breakout board of the rainsensor should also light up
- If one sound is played repeatedly and the light corresponding to the sensor is also blinking repeatedly, probably this rainsensor is not connected correctly and doesn't give a correct input
- If the neopixels are not working at all, or giving strange output, check if the 5V pin is connected to the 3.3V output of the Arduino. Also make sure the dout of each pixel is connected to the din of the pixel after that and not the other way around.
- If your Korg Volca jams completely and you are also not able to play it by hand, you might be sending data to it that it cannot interpret. Check if you are sending messages to the Serial port that are not MIDI messages, this might happen if you are trying to debug something by printing values to the Serial Monitor.
