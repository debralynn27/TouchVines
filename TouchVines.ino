
#include "FastLED.h"
#define NUM_LEDS 50
#define LEDPIN 11
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 140
#define PIRPIN 4


CRGB leds[NUM_LEDS];
// Intervals
unsigned long startTime = millis();
unsigned long firstInterval = 1000UL;
unsigned long secondInterval = 3000UL;
unsigned long thirdInterval = 6000UL;

int val = 1;


void setup() {
 FastLED.addLeds<WS2811,LEDPIN,RGB>(leds,NUM_LEDS);
 pinMode(PIRPIN, INPUT); 
 Serial.begin(9600);
}

void loop() {
  val = digitalRead(PIRPIN);  // read input value
  if (val == HIGH)  {
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    Serial.println(val);
   }
  else {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    Serial.println(val);
   }
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
