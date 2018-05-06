
#include "FastLED.h"
#define NUM_LEDS 50
#define ledpin 11
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 140

CRGB leds[NUM_LEDS];
// Intervals
unsigned long startTime = millis();
unsigned long firstInterval = 1000UL;
unsigned long secondInterval = 3000UL;
unsigned long thirdInterval = 6000UL;


void setup() {
 FastLED.addLeds<WS2811,ledpin,RGB>(leds,NUM_LEDS);
}

void loop() {
  ambient();
  FastLED.show();  
}

void ambient() 
{
  int ambientLow = 30;
  for( int i = 0; i < NUM_LEDS; i++) {
    int val = (((exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0)/4);
    if (val > 35) {
      leds[i] = CHSV(0, 0, val);
    } else {
      leds[i] = CHSV(0, 0, ambientLow);    
    }
  }
}
