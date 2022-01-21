#include<FastLED.h>

//Setup LED strip parameters
#define stripPinA 4 //Const as it does not change. Byte instead of integer as this takes up less memory and value is < 255
#define stripPinB 12
#define stripPinC 13
#define stripPinD 15
#define stripPinE 2
#define NUM_LEDS 142 //Setup for maximum length of larger light tube
byte brightness = 225;
byte saturation = 255;
CRGB leds[NUM_LEDS]; //Setup the array for FastLED control CRGB
int colour_int = 0;
unsigned long timenow = 0;
byte clienton = 0;
int t = 50;
int st = 300;
int num = 1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println("Serial is on");
//LED strip setup
pinMode(stripPinA, OUTPUT);
FastLED.addLeds<WS2812, stripPinA, GRB>(leds, NUM_LEDS); 
FastLED.addLeds<WS2812, stripPinB, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812, stripPinC, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812, stripPinD, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812, stripPinE, GRB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  int n=round(NUM_LEDS/7);
  Serial.println(n);
  
  for (int i=0*n; i<1*n; i++) {
    leds[i]=CRGB::Red;
  }
  for (int i=1*n; i<2*n; i++) {
    leds[i]=CRGB::Orange;
  }
  for (int i=2*n; i<3*n; i++) {
    leds[i]=CRGB::Yellow;
  }
  for (int i=3*n; i<4*n; i++) {
    leds[i]=CRGB::Green;
  }
  for (int i=4*n; i<5*n; i++) {
    leds[i]=CRGB::Blue;
  }
  for (int i=5*n; i<6*n; i++) {
    leds[i]=CRGB::Indigo;
  }
  for (int i=6*n; i<7*n; i++) {
    leds[i]=CRGB::Violet;
  }
  FastLED.show();


}
