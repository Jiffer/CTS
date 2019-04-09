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

int delayval = 50;
float randomR = 0;
float randomG = 0;
float randomB = 0;

int mode = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  randomR = randomR + random(3) - 1;
  randomG = randomG + random(3) - 1;
  randomB = randomB + random(3) - 1;
  Serial.println(randomR ); // + ' ' + randomG + ' ' + randomB
  if (randomR > 255) {
    randomR = 255;
  } else if (randomR < 0) {
    randomR = 0;
  }
  if (randomG > 255) {
    randomG = 255;
  } else if (randomG < 0) {
    randomG = 0;
  }
  if (randomB > 255) {
    randomB = 255;
  } else if (randomB < 0) {
    randomB = 0;
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    
//    Serial.println(255 * ((sin(i * .05)+ 1)*.5));
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(  randomR, randomG, randomB)); // Moderately bright green color.

  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
}
