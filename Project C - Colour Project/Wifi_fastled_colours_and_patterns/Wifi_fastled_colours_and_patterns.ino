//An ever evolving test sketch to learn and understand how to control LEDs using WIFI and the ESP32 controller
//Second version - 03/01/2021 - access point conversion test 2 - Set IP address / addition of HSV and word colour control using structs
//Luminate_Bristol
//Note that this will be comentented to shit in order to help understanding when coming back to the code in the future
///INSTRUCTIONS
//1) Upload this code to ESP32
//2) Press the "Enable" button on the ESP32
//3) Check Serial monitor for IP address
//4) Connect to ESP32 Access Point, use given IP address to control output - note fixed IP code not yet working, need to sort that

//Include libraries
#include <WiFi.h>
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
  
//Configure IP address specifically for the soft access point
//WiFi.softAPConfig(ip, gateway, subnet); //All three variables are needed but only the ip is used by the client

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
else if (c.indexOf("hues") != -1) {
  Serial.println("Chill man, just chill");
  hues();
}
else if (c.indexOf("strobe") != -1) {
  Serial.println("Woah my eyes!");
  strobe();
}
else if (c.indexOf("rainbow") != -1) {
  Serial.println("Pot o gold bro");
  rainbow();
}
else if (c.indexOf("windows") != -1) {
  Serial.println("Bill Gates come at me!");
  windows();
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
    if (pixelnum >= 140) {
    pixelnum = 10;
    colour_int = colour_int + 10;
    fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      checkclient();
    }
  }
}

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
  }
checkclient();
}
}

//Function turn on flashy strobe mode
void strobe() {
  clienton = 0;
  while (clienton == 0) {
    if (millis() >= timenow + st  && num==1) {
      timenow += st;
      fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
      FastLED.show();
      num = num+1;  
      checkclient();
      }
      
      if (millis() >= timenow + st &&  num == 2) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      num = num-1;  
      checkclient();
      }
  }
}

//Function to turn on rainbow mode
void rainbow() {
  int n=round(NUM_LEDS/7); 
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

//Function to turn on windows mode
void windows() {
  int bno = 10;
  int suns[ 10 ][ 3 ] = {{162, 195, 253}, {182, 214, 253}, {63, 143, 254}, {99, 166, 253}, {134, 189, 255}, {58, 90, 55}, {130, 178, 36}, {89, 130, 25}, {62, 91, 13}, {59, 94, 4}};
  int len = 14; 
  for (int i=0; i<=9; i++) {
    for (int n=0; n<=len; n++) {
      leds[(i*len)+n] = CRGB(suns[i][0], suns[i][1], suns[i][2]);
      FastLED.show();
    }
  }
}

//Function to turn on hue changer - not currently working properly!!! Looks sick af tho so left it in haha - note there has to be a better way of using whileloops and client on!!
void hues() {
  clienton = 0;
  while (clienton == 0) {
  byte startcolour = 85;
  byte endcolour = 105;

  //FastLED.setBrightness(brightnesst);
  for (byte bytehue = startcolour; bytehue < endcolour; bytehue++) {
    fill_solid(leds, NUM_LEDS, CHSV(bytehue, saturation, brightness));
    FastLED.show();
    while (millis() >= timenow) {
    timenow += t;
    checkclient();    
    }
    }
    
  for (byte bytehue = endcolour; bytehue > startcolour; bytehue = bytehue - 1) {    
    fill_solid(leds, NUM_LEDS, CHSV(bytehue, saturation, brightness));
    FastLED.show();
    while (millis() >= timenow) {
    timenow += t;
    checkclient();  
  }
  }
}
}



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
