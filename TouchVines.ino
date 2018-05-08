
#include "FastLED.h"
#include <CapacitiveSensor.h>

#define NUM_LEDS 50
#define LEDPIN 11
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 140
#define PIR_PIN 4

CRGB leds[NUM_LEDS];

// Intervals
unsigned long startTime = millis();
unsigned long firstInterval = 1000UL;
unsigned long secondInterval = 3000UL;
unsigned long thirdInterval = 6000UL;

int val = 1;

void setup() {
 FastLED.addLeds<WS2811,LEDPIN,RGB>(leds,NUM_LEDS);
 pinMode(PIR_PIN, INPUT); 
}

void loop() {
    val = digitalRead(PIR_PIN); 
    if (val == HIGH)   {
         aquapaint();
         addYellowGlitter(60);
         startTime = millis();
     }
    else {
        if((millis() - startTime) < firstInterval){ 
          aquapaint();
            } else if ((millis() - startTime) < secondInterval) {
        trailoff1();
            } else if ((millis() - startTime) < thirdInterval) {
        trailoff2();
            } else {
        ambient ();}
     }
  FastLED.show();  
}

void ambient() 
{
  int ambientLow = 30;
  for( int i = 0; i < NUM_LEDS; i++) {
    int val = (((exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0)/4);
    if (val > 35) {
      leds[i] = CHSV(115, 0, val);
    } else {
      leds[i] = CHSV(115, 0, ambientLow);    
    }
  }
}

void aquapaint (){
    for( int i = 0; i < NUM_LEDS; i++) {
    float fractionOfTheWayAlongTheStrip = (float)i / (float)(NUM_LEDS-1);
    uint8_t amountOfBlending = fractionOfTheWayAlongTheStrip * 255;
    CRGB pixelColor = blend( CHSV(100, 255, 255),  CHSV(130, 255, 255), amountOfBlending);
    leds[i] = pixelColor;
  }
}

void addGlitter(fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    CRGB pixelColor = blend( CHSV(100, 255, 255),  CHSV(130, 255, 255), 120);
    leds[ random16(NUM_LEDS) ] += pixelColor;
  }
}

void addYellowGlitter(fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    CRGB pixelColor = CHSV(40, 255, 255);
    leds[ random16(NUM_LEDS) ] += pixelColor;
  }
}

void trailoff1() {
    for( int i = 0; i < NUM_LEDS; i++) {
     leds[i].fadeLightBy(64);
    }
     addGlitter(30); 
}

void trailoff2() {
     for( int i = 0; i < NUM_LEDS; i++) {
       leds[i].fadeLightBy(64);
    }
     addGlitter(10); 
}
