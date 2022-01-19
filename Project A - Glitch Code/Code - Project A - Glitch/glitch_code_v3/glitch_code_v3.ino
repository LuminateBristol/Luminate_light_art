//setup LED strip
#include<FastLED.h>
#define NUM_LEDS 54
#define stripPinA 12
#define stripPinB 10
CRGB leds[NUM_LEDS];

//setup button
int buttonPin = 3;
int buttonState = 0;

//create array containing brightness vs time data. The array has brightness settings at 200ms intervals
int brightness[] = {0, 0, 0, 0, 0, 0, 16, 156, 136, 201, 185, 85, 139, 133, 0, 0, 0, 11, 0, 184, 255, 253, 0, 0, 223, 241, 182, 196, 184, 157, 155, 5, 0, 0, 0, 0, 0};
int t = 200;  //interval time ms
int numt = 37; //number of intervals
int brightnesst = 0;

void setup() {
  pinMode(stripPinA, OUTPUT);
  pinMode(stripPinB, OUTPUT);
  pinMode(buttonPin, INPUT);
  FastLED.addLeds<WS2812, stripPinA>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, stripPinB>(leds, NUM_LEDS);
  Serial.begin(9600); 
}

void loop() {
 
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (buttonState == HIGH) {
    for (int x = 0; x < numt; x = x + 1) {
      brightnesst = brightness[x]/2;
      FastLED.setBrightness(brightnesst);
      leds[0] = CRGB::White;
      fill_solid(leds, NUM_LEDS,CRGB::GhostWhite);
      FastLED.show();
      delay(t);  
    }
  } else {
      fill_solid(leds,NUM_LEDS,CRGB::Black);
      FastLED.show();
      }
}
