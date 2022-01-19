//This is a sketch to run three different led strips on three different data pins. 
//The same glitch animation occurs on all three strips at the same time. This is because three strips make up one light tube. Noice.

//setup LED strips
#include<FastLED.h>
#define NUM_STRIPS 2
#define NUM_LEDS 5 //Assume that number of leds per strip is the same
#define stripPinA 13
#define stripPinB 11

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
  //pinMode(stripPinA, OUTPUT);
  //pinMode(stripPinB, OUTPUT);
  //pinMode(stripPinC, OUTPUT);
  pinMode(buttonPin, INPUT);
  FastLED.addLeds<WS2811, stripPinA, BRG>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, stripPinB, BRG>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, stripPinC, BRG>(leds, NUM_LEDS);
  Serial.begin(9600); 
}

void loop() {
 
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (buttonState == HIGH) {
    for (int x = 0; x < numt; x = x + 1) {
      brightnesst = brightness[x];
      FastLED.setBrightness(brightnesst);   
      fill_solid(leds, NUM_LEDS,CRGB::GhostWhite);
      FastLED.show();
      delay(t);  
    }
  } else {
      fill_solid(leds,NUM_LEDS,CRGB::Black);

      FastLED.show();
      }
}
