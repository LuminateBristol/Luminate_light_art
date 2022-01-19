//setup LED strip
#include<FastLED.h>
#define NUM_LEDS 53
#define stripPinA 12
#define stripPinB 10
CRGB leds[NUM_LEDS];

//create array containing brightness vs time data. The array has brightness settings at 200ms intervals
int brightness[] = {0, 0, 0, 0, 0, 0, 16, 156, 136, 201, 185, 85, 139, 133, 0, 0, 0, 11, 0, 184, 255, 253, 0, 0, 223, 241, 182, 196, 184, 157, 155, 5, 0, 0, 0, 0, 0};
int t = 200;  //interval time ms
int numt = 37; //number of intervals
int brightnesst = 0;

void setup() {
  pinMode(stripPinA, OUTPUT);
  pinMode(stripPinB, OUTPUT);
  FastLED.addLeds<WS2812, stripPinA>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, stripPinB>(leds, NUM_LEDS);
}

void loop() {


    for (int x = 0; x < numt; x = x + 1) {
      brightnesst = brightness[x]/5;
      FastLED.setBrightness(brightnesst);
      //leds[0] = CRGB::White;
      fill_solid(leds, NUM_LEDS,CRGB::GhostWhite);
      FastLED.show();
      delay(t);  
    }
    FastLED.setBrightness(255/5);
    delay(3000);
    fill_solid(leds, NUM_LEDS,CRGB::Blue);
    FastLED.show();
    delay(2000);
    fill_solid(leds, NUM_LEDS,CRGB::Red);
    FastLED.show();
    delay(2000);
    fill_solid(leds, NUM_LEDS,CRGB::Green);
    FastLED.show();
    delay(2000);
    fill_solid(leds, NUM_LEDS,CRGB::Black);
    FastLED.show();
    delay(3000);
      
}
