/////////////////////////////////////////////////////////////////////////////////////
//Title: Header File for Lumiwifi library
//Version: v1
//Date: Sept 2021
//Purpose: Provide header info (class definition) for the Lumiwifi
//         led control library. A library designed to provide read Wifi
//         commands needed for controlling Luminate strips.
//
//Limitations: This v1 code has the following limitations:
//             - Currently set to setting up and checking client only
//             - The Lumistick library does the actual LED control
//
//Author: Henry Hickson
/////////////////////////////////////////////////////////////////////////////////////

#ifndef lumiwifi_h
#define lumiwifi_h

#include "Arduino.h"
#include "WiFi.h"

class Lumiwifi //The class defines all functions and variables used in the library
{
  public:
    //Public Variables / Functions (those used by the user in their code):

    //1. Initialiser function (constructor)
    Lumiwifi();

    //2. Variables note defined in functions
    String strcom;
    IPAddress ip;
    IPAddress subnet;
    IPAddress gateway;
    WiFiServer server;

    //3. Functions
    WiFiServer* configWiFi(char* ssid, char* password, WiFiServer* server);
    String wificheckclient(WiFiServer* server);
    int wifitester(WiFiServer* server);

  private:
    //Private Variables / Functions (those used by the functions in the library only):
    String _test;
    
 };

#endif
