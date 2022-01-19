//======================================================================
//Program to take a large image array from Python CV2 and display the
//image on the Lumistick when moving with long exposure photpgraphy.
//
//Henry Hickson
//March 2021
//
//Accompanying scripts:
//  - Python array compiler - "long_ex_image_outputter.py"
//
//======================================================================

//===========================LED PARAMETERS=============================
#include<FastLED.h>
const byte NUM_LEDS = 5;
const byte img_length = 5;
const byte stripPinA = 2;
const byte blocknum = 72;
const byte brightness = 200;
CRGB leds[NUM_LEDS];
int input_array[img_length][NUM_LEDS][3] = {
{{210,243,252},{121,194,252},{188,230,252},{115,158,22},{66,98,12}},
{{76,147,255},{98,170,253},{173,212,255},{115,163,29},{77,110,20}},
{{190,219,253},{66,149,255},{149,194,253},{119,167,30},{61,96,5}},
{{18,107,250},{46,138,253},{138,191,254},{146,195,50},{55,87,11}},
{{251,254,254},{150,190,249},{188,217,251},{104,152,32},{52,82,16}}
};
const byte time_int = 500;
byte clienton = 0;

//===========================WIFI PARAMETERS============================
#include<WiFi.h>;
const char* ssid = "LuminateAP";
const char* password = "123456789";
WiFiServer server(80);
IPAddress ip(192, 168, 1, 184);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

//==============================SETUP LOOP==============================
void setup() {
  Serial.begin(115200);
  pinMode(stripPinA, OUTPUT);
  FastLED.addLeds<WS2812, stripPinA, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);

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

//===============================VOID LOOP===============================
void loop() {
  checkclient();
}

//============================DEFINE FUNCTIONS============================
void checkclient() {
  WiFiClient client = server.available();
  if (client.available()) {
    clienton = 1;
    String c = client.readStringUntil('\r');
    
    if (c.indexOf("go_time") != -1) {
      long_exposure_light();
    }
}
}

void long_exposure_light() {
  for (byte i=0; i<img_length; i++) {
    for (byte j=0; j<NUM_LEDS; i++) {
      leds[j] = CRGB(input_array[i][j][1], input_array[i][j][2], input_array[i][j][3]);
    }
    FastLED.show();
    delay(time_int);
  }
}
