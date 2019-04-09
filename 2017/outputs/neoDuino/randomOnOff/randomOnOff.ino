// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayVal; // delay for half a second
int brightnessVal;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {

  int randomR = random(255);
  int randomG = random(255);
  int randomB = random(255);
  int randomLight = random(NUMPIXELS);


  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(randomLight, pixels.Color(randomR, randomG, randomB));
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(100); // Delay for a period of time (in milliseconds).


  // turn off:
  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(randomLight, pixels.Color(0, 0, 0)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(50); // Delay for a period of time (in milliseconds).

}
