/////////////////////////////////////////////////////////////////////////////////////
//Title: .cpp File for Lumistick Library
//Version: v1
//Date: Sept 2021
//Purpose: Provide cpp info (functions) for the Lumiwifi
//         WiFi command reading library
//
//Limitations: This v1 code has the following limitations:
//              - Command reading and provision only
//
//Author: Henry Hickson
/////////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "WiFi.h"
#include "lumiwifi.h"

//----------------------------------CONSTRUCTOR---------------------------------------
//Constructor to create an instance for the lumiwifi.h class
//This sets up an instance for each of the led sticks to be controlled
Lumiwifi::Lumiwifi() {
    Serial.begin(115200);
}

//----------------------------------FUNCTIONS------------------------------------------
WiFiServer* Lumiwifi::configWiFi(char* ssid, char* password, WiFiServer* server) {
    server = new WiFiServer(80);
    IPAddress ip(192, 168, 1, 184);
    IPAddress gateway(192,168,4,9);
    IPAddress subnet(255,255,255,0);

    //Wifi Access Point Setup
    Serial.println("Setting AP (Access Point)...");
    Serial.println("ssid: LuminateAP");
    Serial.println("Please connect and enter password.");
    WiFi.softAP(ssid,password);
    Serial.println(WiFi.softAPIP());

    server->begin();    //We use -> when working with pointers
    return server; 
}

String Lumiwifi::wificheckclient(WiFiServer* server) {
    WiFiClient client = server->available();
    if (client.available()) {
        String c = client.readStringUntil('\r');
        return c;
    } 
    else {
        return "null";
    }
}

int Lumiwifi::wifitester(WiFiServer* server) {
    String _test = wificheckclient(server);
    Serial.println(_test);
    return 100;
}
