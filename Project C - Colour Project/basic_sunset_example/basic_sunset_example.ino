#include<FastLED.h>
//Setup LED strip parameters
#define stripPinA 2 //Const as it does not change. Byte instead of integer as this takes up less memory and value is < 255
#define NUM_LEDS 142 //Setup for maximum length of larger light tube
CRGB leds[NUM_LEDS]; //Setup the array for FastLED control CRGB
int bno = 10;
int suns[ 10 ][ 3 ] = {{147, 41, 1}, {253, 206, 36}, {254, 146, 20}, {254, 193, 24}, {249, 71, 3}, {249, 134, 26}, {250, 141, 44}, {158, 17, 3}, {243, 169, 15}, {242, 140, 46}};
int len = 14; 

void setup() {
//LED strip setup
pinMode(stripPinA, OUTPUT);
FastLED.addLeds<WS2812, stripPinA, GRB>(leds, NUM_LEDS); 
Serial.begin(115200);
}

//Function to turn on sunset  from sunset image pixelator used in Python
//Define array - use 10 blocks
void loop() {
  Serial.println("hello?");
    for (int i=0; i <= 9; i++) {
    Serial.println(i);
    for (int n = 0; n <= len; n++) {
    leds[(i*len)+n] = CRGB(suns[i][0], suns[i][1], suns[i][2]);
    Serial.println(suns[i][2]);
    FastLED.show();
    }
  }
    
  delay(5000);
}
