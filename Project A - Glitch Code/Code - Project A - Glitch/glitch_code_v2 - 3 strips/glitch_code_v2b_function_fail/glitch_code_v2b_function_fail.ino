//This is a sketch to run three different led strips on three different data pins. 
//The same glitch animation occurs on all three strips at the same time. This is because three strips make up one light tube. Noice.

//setup LED strips
#include<FastLED.h>
#define NUM_STRIPS 3
#define NUM_LEDS 5 //Assume that number of leds per strip is the same
#define stripPinA 11
#define stripPinB 12
#define stripPinC 13
CRGB ledsA[NUM_LEDS];
CRGB ledsB[NUM_LEDS];
CRGB ledsC[NUM_LEDS];

//setup button
int buttonPin = 3;
int buttonState = 0;
int t = 200; //interval time ms
int brightness[] = {0, 0, 0, 0, 0, 0, 16, 156, 136, 201, 185, 85, 139, 133, 0, 0, 0, 11, 0, 184, 255, 253, 0, 0, 223, 241, 182, 196, 184, 157, 155, 5, 0, 0, 0, 0, 0};
int numt = 37; //number of intervals
int brightnesst = 0;

void setup() {
  pinMode(stripPinA, OUTPUT);
  pinMode(stripPinB, OUTPUT);
  pinMode(stripPinC, OUTPUT);
  pinMode(buttonPin, INPUT);
  FastLED.addLeds<WS2811, stripPinA, BRG>(ledsA, NUM_LEDS);
  FastLED.addLeds<WS2811, stripPinB, BRG>(ledsB, NUM_LEDS);
  FastLED.addLeds<WS2811, stripPinC, BRG>(ledsC, NUM_LEDS);
  Serial.begin(9600); 

}

//Create a function for all leds in the tube to change colour (3 strips)
void changecolour(CRGB colour){
  fill_solid(ledsA, NUM_LEDS,CRGB::colour);
  fill_solid(ledsB, NUM_LEDS,CRGB::colour);
  fill_solid(ledsC, NUM_LEDS,CRGB::colour);
  FastLED.show();
  } 
}
  
void loop() {
 
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  for (int x = 0; x < numt; x = x++) {
      brightnesst = brightness[x];
      FastLED.setBrightness(brightnesst);   
      changecolour(GhostWhite);
      delay(t);  
    }
  } else {
      changecolour(black);      
      FastLED.show();
      }
}


  
