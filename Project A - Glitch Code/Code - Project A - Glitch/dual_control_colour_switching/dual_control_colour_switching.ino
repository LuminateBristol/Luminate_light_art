//setup LED strip
#include<FastLED.h>
#define NUM_LEDS 53
#define stripPinA 12
#define stripPinB 11
#define stripPinC 10
#define stripPinD 9
CRGB leds[NUM_LEDS];

int t = 100;  //interval time ms
int brightnesst = 200;
int nocolours = 5;
uint32_t colours[] = {CRGB::Teal, CRGB::Purple, CRGB::Red, CRGB::Yellow, CRGB::Green};

void setup() {
  pinMode(stripPinA, OUTPUT);
  pinMode(stripPinB, OUTPUT);
  pinMode(stripPinC, OUTPUT);
  pinMode(stripPinD, OUTPUT);
  FastLED.addLeds<WS2812, stripPinA>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, stripPinB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, stripPinC>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, stripPinD>(leds, NUM_LEDS);
}

void loop() {
   FastLED.setBrightness(brightnesst);
   for(int x=0; x<nocolours; x++) {
    fill_solid(leds, NUM_LEDS, colours[x]);
    FastLED.show();
    delay(t);
   }
      
}
