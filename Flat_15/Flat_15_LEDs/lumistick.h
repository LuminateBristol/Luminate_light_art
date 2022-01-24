/*
//Title: Header File for Lumistick Library
//Version: v2
//Date: Sept 2021
//Purpose: Provide header info (class definition) for the Lumistick
//         led control library. A library designed to run different LED
//         patterns on Luminate linear devices such as the Lumistick.
//
//Limitations: This v1 code has the following limitations:
//              - Single tube
//              - Defines LED control functions only. WiFi/Midi setup and control
//                are not included in this library.
//              - Limited, predefined functions
//
//Author: Henry Hickson
*/

#ifndef lumistick_h
#define lumistick_h

#include "Arduino.h"
#include "FastLED.h"
#include "lumiwifi.h"

class Lumistick 
//The class defines all functions and variables used in the library
{
  public:
    //Public Variables / Functions (those used by the user in their code):
    Lumiwifi lumiwifi;
    #define NUM_LEDS 100
    CRGB ledset[NUM_LEDS];
    String c;
    WiFiServer* server;
    byte t = 50;
    byte num = 1;
    unsigned long timenow = 0;

    byte _clienton = 0;

    //Initialiser function (constructor)
    Lumistick();

    //Functions
    void initiate_stick(String client_type, char* ssid, char* password);
    void checkfastled();
    void checkclient(byte brightness, byte saturation);
    void lightitup(String colour, byte brightness, byte saturation, int colour_int);
    void LEDoff();
    void floatyboi(int colour_int, byte brightness, byte saturation);
    void clrs(int colour_int, byte brightness, byte saturation);
    void strobe(byte brightness, byte saturation);
    void rainbow();

  private:
    String action ;
    String _colour;
    int _i;
    int _x;
    byte _pixelnum;
    
    WiFiServer* _server;

};

#endif
