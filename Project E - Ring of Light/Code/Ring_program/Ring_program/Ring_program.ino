////////////////////////////////////////////////////////////////////////////////
//Project: Ring Program for Luminate Project E - Ring of Light
//Date: 29/07/21
//
//Description: This code has a series of light programs that are used on the
//             Luminate Ring of Light. These are selected via very basic WiFi
//             web page commands where the used connects to the ESP32 acting
//             acting as an Access Point. Not ideal control but very portable.
//             There is also a random mode which picks one and plays it between
//             1 and 10 times
//
////////////////////////////////////////////////////////////////////////////////

//Include libraries
#include <WiFi.h>
#include<FastLED.h>

//Setup LED strip parameters
#define stripPinA 4 
#define stripPinB 12
#define stripPinC 13
#define stripPinD 15
#define stripPinE 2
#define NUM_LEDS 126 //Setup fornumber of LEDs in the Ring of Light
byte brightness = 225; 
byte saturation = 255;
CRGB leds[NUM_LEDS]; //Setup the array for FastLED control CRGB
int colour_int = 0;
unsigned long timenow = 0;
byte clienton = 0;
int t = 50;
int st = 100;
int num = 1;
int breakclause = 0;
 
//Setup Wifi Parameters
const char* ssid     = "LuminateAP"; //Setup access point name
const char* password = "123456789"; //Setup access point password. Minimum 9 characters. For open network, leave blank?
// Set web server port number to 80
WiFiServer server(80);
//Set IP Address
IPAddress ip(192, 168, 1, 184);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

void setup() {
//Start Serial
Serial.begin(115200);
Serial.println("Serial is on");
//LED strip setup
pinMode(stripPinA, OUTPUT);
FastLED.addLeds<WS2812, stripPinA, GRB>(leds, NUM_LEDS); 
FastLED.addLeds<WS2812, stripPinB, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812, stripPinC, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812, stripPinD, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812, stripPinE, GRB>(leds, NUM_LEDS);
  
//Wifi Access Point Setup
Serial.println("Setting AP (Access Point)...");
Serial.println("ssid: LuminateAP");
Serial.println("Please connect and enter password.");
WiFi.softAP(ssid, password); //Start up the Soft Access Point mode with the given ssid and password
IPAddress IP = WiFi.softAPIP(); //Whether the IP address is default or preset, this will define new parameter IP with the ip address

//Output details to serial
Serial.print("AP IP address: ");
Serial.println(IP);

//Start the ESP32 as a soft access point web server  
server.begin(); 
}

void loop() {
checkclient();
}

//---------------------------------DEFINE FUNCTIONS---------------------------------------
//Function to check if a command from the client is incoming and react to it
void checkclient() {
WiFiClient client = server.available();
if (client.available()) {
clienton=1; //This is needed as the animations are currently setup in while loops where clienton = 0. There is probably a better way to do this, need to work it out!
breakclause=0; //This is to reset the breakclause to make sure all while loops still run
//Read client input and react accordingly
String c = client.readStringUntil('\r'); //Read client message as a string. The alternative to this is to client.read() which produces a character then convert this to a string.

if (c.indexOf("col") != -1) { //indexOf returns the index of the statement within a string. If the statement is not in the string, it returns -1. 
                              //This therefore asks if this string is within the client's string input
  int i = c.indexOf("HTTP");
  Serial.println(i);
  String colour = c.substring(8,i-1); //Substring(from, to) returns the string from index "from" to the optional index "to". Here we want the string just after the word "col"
  Serial.print("Changing colour of light stick to...");
  Serial.println(colour);
  lightitup(colour);
}
else if (c.indexOf("floatyboi") != -1) { //indexOf returns the index of the statement within a string. If the statement is not in the string, it returns -1. 
                                         //This therefore asks if this string is within the client's string input
  Serial.println("This is LIT");
  floatyboi();
}
else if (c.indexOf("clrs") != -1) {
  Serial.println("Ooh pretty colours");
  clrs();
}
else if (c.indexOf("strobe") != -1) {
  Serial.println("Woah my eyes!");
  strobe();
}
else if (c.indexOf("round") != -1) {
  Serial.println("Roundabout time!");
  roundy();
}
else if (c.indexOf("fades") != -1) {
  Serial.println("OOh chill");
  fades();
}
else if (c.indexOf("fadewhite") != -1) {
  Serial.println("OOh chill in white");
  fadeswhite();
}
else if (c.indexOf("randomise") != -1) {
  Serial.println("Randomise this shit");
  randomisecheat();
}
else if (c.indexOf("off") != -1) {
  Serial.println("Nah, this ain't lit no more");
  LEDoff();
}

//Once there is no more client communication, close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
//-------------------------------------------------------------------------------------------------------------------------------
//Function to turn on LEDs with a songle colour depending on HSV code or on colour name from predefined list
void lightitup(String colour) {
//This setup currently only works for a selection of CRGB colours and all HSV numbers
//-basic I know, really I need to build an HTML interface that puts all this in the background but this will have to do for now

//Step 1 - create a structural array linking HSV values to predefined colour names
//A data struct for each colour is needed, data structs allow us to combine different data types into the same array thing
struct HSVcolour{ //Define the structure of the colour data structs
  String HSVcol;
  int HSVno;
};

struct HSVcolour HSVcolours[10] = { //Define an array of 10 structures, these are the String colour options that we can call. This stores 10 elements of struct colour.
  {"red", 1}, //Create data struct for each colourm we have already defined the structure so now all we need to do is fill it
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
  if (HSVcolours[x].HSVcol == colour) { //HSVcolours[i].HSVcol calls the ith elemnent in the array and the HSVcol part of the structure
    colour_int = HSVcolours[x].HSVno;
    //Serial.print("Change to HSV colour code: ");
    //Serial.println(colour_int);
  }
}
}
if (colour_int == 0) { 
//Check if the string is an HSV colour code
if (colour.toInt() >= 0 && colour.toInt() <= 255) {
    colour_int = colour.toInt(); 
    //Serial.print("Change to HSV colour code: ");
    //Serial.println(colour_int); 
}
}
if (colour_int == 0) {
  //Return error if any other string is recieved as it does not fit within our parameters
    Serial.println("Error, that is not a colour or colour code value");
    return;  
}

//Step 3 - Light up leds baby
Serial.print("Change to HSV colour code: ");
Serial.println(colour_int);
fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
FastLED.show();
colour_int=0;
}

//Function to turn off LEDs completely i.e. turn LEDs black
void LEDoff() {
fill_solid(leds, NUM_LEDS, CRGB::Black);
FastLED.show();
}
//-------------------------------------------------------------------------------------------------------------------------------
//Function to turn on floatyboi routine - note there has to be a better way of using whileloops and client on!!
void floatyboi() {
  byte pixelnum = 10;
  clienton = 0;
  while (clienton == 0) {
    if (millis() >= timenow + t && pixelnum<NUM_LEDS) {
      timenow += t;
      pixelnum=pixelnum+10;
      fill_solid(leds, pixelnum, CHSV(colour_int, saturation, brightness));
      FastLED.show();  
    }
    checkclient();
    if (pixelnum >= NUM_LEDS) {
    pixelnum = 10;
    colour_int = colour_int + 10;
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    checkclient();
    }
    if (breakclause == 1) {
      clienton=1;
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------
//Function to turn on LED hue changer through all colours - note there has to be a better way of using whileloops and client on!!
void clrs() {
  clienton = 0;
  while (clienton == 0) {
    if (millis() >= timenow + t) {
      timenow += t;
      colour_int++;
      fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
      FastLED.show();  
      checkclient();
      if (breakclause == 1) {
      clienton=1;
    }
  }
checkclient();
}
}
//-------------------------------------------------------------------------------------------------------------------------------
//Function turn on flashy strobe mode
void strobe() {
  clienton = 0;
  while (clienton == 0) {
    if (millis() >= timenow + st  && num==1) {
      num = num+1; 
      timenow += st;
      fill_solid(leds, NUM_LEDS, CRGB::White);
      FastLED.show(); 
      checkclient();
      }
      
      if (millis() >= timenow + st &&  num == 2) {
      num = num-1; 
      LEDoff(); 
      checkclient();
      }
      if (breakclause == 1) {
      clienton=1;
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------
void colourfortime(int tnum, int mnum) {
  clienton=0;
  byte count = 0;
  while (clienton == 0 && count < mnum){
    if (millis() >= timenow + tnum) {
      timenow += tnum;
      count++;
      fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
      FastLED.show();
    }
    checkclient();
    Serial.print(breakclause);
    if (breakclause == 1) {
      if (millis() >= timenow + tnum) {
        return;
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------
void roundy() {
  clienton = 0;
  byte pixelnum = 0;
  while (clienton == 0) {
      if (millis() >= timenow && pixelnum<NUM_LEDS) {
        timenow += t*1.25;
        pixelnum++;
        fill_solid(leds, pixelnum, CRGB::White);
        FastLED.show();
        checkclient();
      }
      if (pixelnum >= NUM_LEDS) {
      pixelnum = 0;
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      checkclient();
      }
      if (pixelnum >= NUM_LEDS && breakclause == 1) {
      return;
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------
void fades() {
    clienton = 0;
    byte count = 0;
    byte n=5;
    while (clienton == 0) {
      if (millis() >= timenow + t) {
        timenow += t;
        count += n;
        fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, count));
        FastLED.show();  
      }
      if (count == 255) {
        n=-5;
      }
      if (count == 0 ){
        n=1;
      }
      checkclient();
    }
}
//-------------------------------------------------------------------------------------------------------------------------------
void fadeswhite() {
    clienton = 0;
    byte count = 0;
    byte n=5;
    while (clienton == 0) {
      if (millis() >= timenow + t) {
        timenow += t;
        count += n;
        fill_solid(leds, NUM_LEDS, CRGB::White);
        FastLED.show();  
      }
      if (count == 255) {
        n=-5;
      }
      if (count == 0 ){
        n=1;
      }
      checkclient();
    }
}
//-------------------------------------------------------------------------------------------------------------------------------
//NOT WORKING AAAARGH
void randomise() {
  clienton = 0;
  breakclause = 1;
  
  while (clienton == 0) {
    byte rand1 = random(1,5);
    byte rand2 = random(1,6);
    if (rand2 == 1) {
      colourfortime(t*40, rand1);
    } 
    else if (rand2 == 2) {
      for (byte rep = 0; rep<rand1; rep++) {
        roundy();
      }
    }
    else if (rand2 == 3) {
      for (byte rep = 0; rep<rand1*50; rep++) {
        strobe();
      }
    }
    else if (rand2 == 4) {
      for (byte rep = 0; rep<rand1; rep++) {
        clrs();
      }
    }
    else if (rand2 == 5) {
      for (byte rep = 0; rep<rand1; rep++) {
        floatyboi();
      }
    }
  }
  checkclient(); 
}
//-------------------------------------------------------------------------------------------------------------------------------
//The cheat version...
void randomisecheat() {
  clienton = 0;
  
  while (clienton == 0) { 
    byte rand1 = byte(random(1,8));
    byte rand2 = byte(random(0,6));
    byte count = 0;
    Serial.println(rand2);
   
    if (rand2 == 1) { //holdcolour
      while (clienton == 0 && count <= rand1) {
        if (millis() >= timenow + t) {
          timenow += 3000;
          count++;
          fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
          FastLED.show();
        }
        checkclient();
      }
    }
    
    else if (rand2 == 2) { //strobe
      byte num = 1;
        while (clienton == 0 && count < rand1*10) {
          if (millis() >= timenow + st  && num==1) {
            num = num+1; 
            timenow += st;
            fill_solid(leds, NUM_LEDS, CRGB::White);
            FastLED.show(); 
            checkclient();
            }
      
           if (millis() >= timenow + st &&  num == 2) {
           num = num-1; 
           LEDoff(); 
           checkclient();
           }
           checkclient();
           count++;
          }
    }
    
    else if (rand2 == 3) { //colours
          while (clienton == 0 && count < 5) {
            if (millis() >= timenow + t) {
              timenow += t;
              colour_int++;
              fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
              FastLED.show();
              checkclient();
              if (colour_int >= 254) {
                count++;
              }
            }
            checkclient();
          }
      }

    else if (rand2 == 4) { //floaty
      byte pixelnum = 10;
      byte count2=0;
        while (clienton == 0 && count<2) {
          if (millis() >= timenow + t && pixelnum<NUM_LEDS) {
            timenow += t;
            pixelnum=pixelnum+10;
            fill_solid(leds, pixelnum, CHSV(colour_int, saturation, brightness));
            FastLED.show();  
          }
          checkclient();
          
          if (pixelnum >= 126) {
            pixelnum = 10;
            colour_int = colour_int + 10;
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            FastLED.show();
            count2++;
            if (count2 >= 25) {
              count++;
            }
          }
          checkclient(); 
        }
    }

    else if (rand2 == 5) { //roundy
          byte pixelnum = 0;
          while (clienton == 0 && count<rand1) {
            if (millis() >= timenow && pixelnum<NUM_LEDS) {
              timenow += t*1.25;
              pixelnum++;
              fill_solid(leds, pixelnum, CRGB::White);
              FastLED.show();
           }
           checkclient();
           if (pixelnum >= NUM_LEDS) {
             pixelnum = 0;
              fill_solid(leds, NUM_LEDS, CRGB::Black);
              FastLED.show();
              count++;
              }
          }
    }
}
}
    
//-------------------------------------------------------------------------------------------------------------------------------

//Function to output status of the Wifi (taken from Arduino code website)
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
