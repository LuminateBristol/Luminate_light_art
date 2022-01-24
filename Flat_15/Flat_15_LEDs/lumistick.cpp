/*
//Title: .cpp File for Lumistick Library
//Version: v2
//Date: Sept 2021
//Purpose: Provide cpp info (functions) for the Lumistick
//         led control library. A library designed to run different LED
//         patterns on Luminate linear devices such as the Lumistick.
//
//Limitations: This v1 code has the following limitations:
//              - Single tube - single strip pin - need to work out how to apply to multiple
//              - Defines LED control functions only.
//              - WiFi control only, MIDI and other clients to be added
//              - Limited, predefined functions
//              - WS2812B, GRB setup only - can be adjusted with additional inputs though
//              - Lightitup - limited to full tube - could add pixelnum argument
//              - Pattern function colour_int resets to 0 each time - would nice to have colour_int live
//              - Floaty - limited to blocks of 10 - could add increment argument
//
//Author: Henry Hickson
*/

#include "Arduino.h";
#include "FastLED.h";
#include "lumistick.h";

//Constructor to create an instance for the lumistick.h class
//This sets up an instance for each of the led sticks to be controlled
Lumistick::Lumistick() {
}

void Lumistick::initiate_stick(String client_type, char* ssid, char* password) {
  /*Function to initiate the Lumistick
   */
  pinMode(4, OUTPUT);
  FastLED.addLeds<WS2812, 4, GRB>(ledset,NUM_LEDS);
  if (client_type == "WiFi"){
    //Switch to an internal pointer ready for checkclient command
    //Note that these inputs are defined in the .h file
    _server=lumiwifi.configWiFi(ssid,password,server); 
  }
}

void Lumistick::checkclient(byte brightness, byte saturation) {
/* Function to check the status of the client and change the LEDs accordingly.
 * Currently only setup for WiFi control but could be expanded for MiDi etc
 */
    c = lumiwifi.wificheckclient(_server);
    if (c != "null") {
      _clienton = 1;
    }
    else {
      return;
    }
    if (c.indexOf("col") != -1) {
      int _i = c.indexOf("HTTP");
      String _colour = c.substring(8,_i-1); 
      lightitup(_colour, brightness, saturation, 0);
      Serial.println("LIGHTITYEAHHH");
    }
    else if (c.indexOf("off") != -1) {
      Serial.println("Nah, this ain't lit no more");
      LEDoff();
    }
    else if (c.indexOf("floatyboi") != -1) { //indexOf returns the index of the statement within a string. If the statement is not in the string, it returns -1.
                                            //This therefore asks if this string is within the client's string input
      Serial.println("This is LIT");
      floatyboi(0, brightness, saturation);
    }
    else if (c.indexOf("clrs") != -1) {
      Serial.println("Ooh pretty colours");
      clrs(0, brightness, saturation);
    }
    else if (c.indexOf("strobe") != -1) {
      Serial.println("Woah my eyes!");
      strobe(brightness, saturation);
    }
    else if (c.indexOf("rainbow") != -1) {
      Serial.println("Pot o gold bro");
      rainbow();
    }
  }


void Lumistick::lightitup(String colour, byte brightness, byte saturation, int colour_int) {
  /* Function to turn on LEDs with a songle colour depending on HSV code or on colour name from predefined list
   * This setup currently only works for a selection of CRGB colours and all HSV numbers
   * Ideally need to pull out the string defined colours and get those to call on the HSV colour code, would be neater
   * Step 1 - create a structural array linking HSV values to predefined colour names
   * A data struct for each colour is needed, data structs allow us to combine different data types into the same array thing
    */

  //Define the structure of the colour data structs
  struct HSVcolour{ 
    String HSVcol;
    int HSVno;
  };

  //Define an array of 10 structures, these are the String colour options that we can call. This stores 10 elements of struct colour.
  //Create data struct for each colourm we have already defined the structure so now all we need to do is fill it
  struct HSVcolour HSVcolours[10] = { 
    {"red", 1}, 
    {"orange",20},
    {"yellow",32},
    {"lightgreen",64},
    {"darkgreen",95},
    {"teal",115},
    {"lightblue",135},
    {"darkblue", 165},
    {"purple",200},
    {"pink",224}
  };

  //Step 2 - interpret the client's request
  if (colour_int == 0) {
  //Check if string is in our predefined list of colours
  for (int x=0; x<10; x++){
    //HSVcolours[i].HSVcol calls the ith elemnent in the array and the HSVcol part of the structure
    if (HSVcolours[x].HSVcol == colour) { 
      colour_int = HSVcolours[x].HSVno;
    }
  }
 }
  if (colour_int == 0) {
  //Check if the string is an HSV colour code
  if (colour.toInt() >= 0 && colour.toInt() <= 255) {
      colour_int = colour.toInt();
  }
  }
  if (colour_int == 0) {
    //Return error if any other string is recieved as it does not fit within our parameters
     Serial.println("Error, that is not a colour or colour code value");
     return;
  }

  //Step 3 - Light up leds
  Serial.print("Change to HSV colour code: ");
  Serial.println(colour_int);
  fill_solid(ledset, NUM_LEDS, CHSV(colour_int, saturation, brightness));
  FastLED.show();
}

//Function to turn off LEDs
void Lumistick::LEDoff() {
    fill_solid(ledset, NUM_LEDS, CRGB::Black);
    FastLED.show();
}


void Lumistick::floatyboi(int colour_int, byte brightness, byte saturation) {
  /* Function to turn on floatyboi routine - note there has to be a better way of using whileloops and client on!!
   */
  _pixelnum = 0;
  _clienton = 0;
  while (_clienton == 0) {
    if (millis() >= timenow + t) {
      timenow += t;
      _pixelnum=_pixelnum+5;
      fill_solid(ledset, _pixelnum, CHSV(colour_int, saturation, brightness));
      FastLED.show();
    }
    checkclient(brightness, saturation);
    if (_pixelnum >= 124) {
      _pixelnum = 5;
      colour_int = colour_int + 10;
      LEDoff();
    }
    checkclient(brightness, saturation);
  }
}

void Lumistick::clrs(int colour_int, byte brightness, byte saturation) {
  /* Function to fade between colours
   */
  _clienton = 0;
  while (_clienton == 0) {
    if (millis() >= timenow + t) {
      timenow += t;
      colour_int++;
      fill_solid(ledset, NUM_LEDS, CHSV(colour_int, saturation, brightness));
      FastLED.show();
      checkclient(brightness, saturation);
    }
  checkclient(brightness, saturation);
  }
}

void Lumistick::strobe(byte brightness, byte saturation) {
  /* Function to turn on strobe mode
   */
  _clienton = 0;
  while (_clienton == 0) {
    if (millis() >= timenow  && num==1) {
      timenow += t*14;
      fill_solid(ledset, NUM_LEDS, CRGB::White);
      FastLED.show();
      num = num+1;
    }
    if (millis() >= timenow &&  num == 2) {
      timenow += t*14;
      LEDoff();
      num = num-1;
    }
    checkclient(brightness, saturation);
  }
}

void Lumistick::rainbow() {
  /* Function to turn on the rainbow mode
   */
  int n=round(NUM_LEDS/7);
  for (int i=0*n; i<1*n; i++) {
    ledset[i]=CRGB::Red;
  }
  for (int i=1*n; i<2*n; i++) {
    ledset[i]=CRGB::Orange;
  }
  for (int i=2*n; i<3*n; i++) {
    ledset[i]=CRGB::Yellow;
  }
  for (int i=3*n; i<4*n; i++) {
    ledset[i]=CRGB::Green;
  }
  for (int i=4*n; i<5*n; i++) {
    ledset[i]=CRGB::Blue;
  }
  for (int i=5*n; i<6*n; i++) {
    ledset[i]=CRGB::Indigo;
  }
  for (int i=6*n; i<7*n; i++) {
    ledset[i]=CRGB::Violet;
  }
  FastLED.show();
}
