#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    20

CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}

void loop() {

  leds[0] = 0xFF007F;
  leds[0].fadeLightBy(250);
  FastLED.show();
  delay(500);  
  leds[1] = CRGB(0, 0, 255);
  leds[1].fadeLightBy(250);
  FastLED.show();
  delay(500);
  leds[2] = CRGB(255, 200, 20);
  leds[2].fadeLightBy(0);
  FastLED.show();
  for (int fadeAmount = 0; fadeAmount <256; fadeAmount +=5) { 
    leds[2].fadeToBlackBy(fadeAmount);  
    FastLED.show();
    delay(10);  
}
  

  delay(5000); 

 for (int bright = 1; bright <256; bright += 3) {
    leds[2] = CRGB(bright, bright * 200 / 255, bright * 20 / 255);
    FastLED.show();
    delay(10);
  }
}