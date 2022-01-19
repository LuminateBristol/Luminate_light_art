#include <WiFi.h>
#include <lumistick.h>
unsigned long time_update;
unsigned long update_stick = 500;
char* ssid = "LuminateZenDen";
char* password = "123456789";

Lumistick lumistick;
  
String client_type ="WiFi";
byte brightness = 255;
byte saturation = 200;
    
void setup() {
    lumistick.initiate_stick(client_type, ssid, password);
}

void loop() {
  unsigned long current_time = millis();
  unsigned long elapsed_time = current_time - time_update;

  if (elapsed_time > update_stick) {
    lumistick.checkclient(brightness, saturation);
    time_update = millis();
  }  
}
