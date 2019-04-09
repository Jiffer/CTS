// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      150

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1;
float randomR = 150;
float randomG = 150;
float randomB = 150;

//
float randomAscent = 0; //
boolean bubble = false;
int bubbleLocations[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int bubblePointer = 0;
long nextReleaseTime = 0;

int historyPointer = 0;

int mode = 5;

int counter = 0;
float decayingLevel = 0;

unsigned long modeTimer = 0;
int timeout = 5000; // 10 seconds per mode

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
  int micLevel = abs(map(analogRead(A0), 0, 1023, -75, 125)); // will give a number between 0 and 125
  if (micLevel > decayingLevel && micLevel > 5) {
    decayingLevel = micLevel;
  }
  else {
    decayingLevel *= .99;
  }
  if (millis() - modeTimer > timeout){
    mode++;
    mode%=10;
    modeTimer = millis();
  
  }

  if (mode == 0) {
    // random walkers
    randomR = randomR + random(-5, 6) ;
    randomG = randomG + random(-5, 6) ;
    randomB = randomB + random(-5, 6) ;
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
  }
  else if (mode == 1) {

    if (micLevel > 5) {
      for (int i = 0; i < NUMPIXELS; i++) {
        //    Serial.println(255 * ((sin(i * .05)+ 1)*.5));
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        float wave = 10 * ((sin((i + counter) * .15) + 1) * .5);
        float waveg = 10 * ((sin((i + counter) * .33) + 1) * .5);
        float waveb = 120 * ((sin((i + counter) * .4) + 1) * .5);
        pixels.setPixelColor(i, pixels.Color( wave , waveg, waveb)); 
      }
      counter++;
    }
    if (micLevel > 10) {
      counter = counter + 1;
    }
    if (micLevel > 20) {
      counter = counter + 2;
    }
  }

  else if (mode == 2) {
    for (int i = 0; i < NUMPIXELS; i++) {
      //    Serial.println(255 * ((sin(i * .05)+ 1)*.5));
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      float wave = 10 * ((sin((i + counter) * .015) + 1) * .5);
      float waveg = 10 * ((sin((i + counter) * .033) + 1) * .5);
      float waveb = 120 * ((sin((i + counter) * .04) + 1) * .5);
      if (micLevel > 5) {
        pixels.setPixelColor(i, pixels.Color( 0 , 0, 0));
      }

      else {
        pixels.setPixelColor(i, pixels.Color( wave , waveg, waveb));
      }
    }
    counter++;
  }
  else if (mode == 3) {
    if (micLevel > 5) {
      bubbleLocations[bubblePointer] = 0;
      bubblePointer++;
      bubblePointer %= 20;

    }
    for (int i = 0; i < NUMPIXELS; i++) {
      boolean turnOff = false;
      for (int j = 0; j < 20; j++) {
        if (abs(i - bubbleLocations[j]) < 3)
        {
          turnOff = true;
        }
      }
      if (turnOff) {
        pixels.setPixelColor(i, 0, 0, 0);
      }
      else {
        pixels.setPixelColor(i, 50, 50, 50);
      }
    }

    // move all bubbles
    for (int i = 0; i < 20; i++) {
      bubbleLocations[i]++;
    }
  }

  else if (mode == 4) {
    

  }
  else if (mode == 5) {
    for (int i = 0; i < 5; i++) {
      
      int index = ((int)(decayingLevel*3 + 30 * i)) % NUMPIXELS;
    
      
      pixels.setPixelColor(index, micLevel * 15, micLevel * 15, micLevel * 20);
    }
   
  }
  else if (mode == 6) {
    int lev = map(analogRead(A0), 0, 1023, 0, 55);
    for (int i = 0; i < NUMPIXELS - 1; i++) {
      pixels.setPixelColor(i, pixels.Color(lev, lev, lev));
    }
  }
  else if (mode == 7) {
    if (micLevel > 5) {
      pixels.setPixelColor(random(NUMPIXELS + 1), pixels.Color(random(255), random(255), random(255)));
    }
    else {
      pixels.setPixelColor(random(NUMPIXELS + 1), pixels.Color(0, 0, 0));
    }
  }
  else if (mode == 8) {
    for (int i = 0; i < 5; i++) {
      pixels.setPixelColor((historyPointer + 30 * i) % NUMPIXELS, micLevel * 15, micLevel * 15, micLevel * 20);
    }

    historyPointer++;
    historyPointer %= NUMPIXELS;
    float delayValue = 10 * (1 + sin(0.01 * millis() / (2 * PI)));
    delay(delayValue);
  }
  else if (mode == 9) {
    for (int i = 0; i < NUMPIXELS - 1; i++) {
      float colorLev = decayingLevel * 10;
      if (colorLev > 255) {
        colorLev = 255;
      }

      pixels.setPixelColor(i, colorLev, colorLev, colorLev );
    }
//    delay(1);
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

}

