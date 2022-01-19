#include <WiFi.h>
#include <lumistick.h>
unsigned long time_update;
unsigned long update_stick = 100;
char* ssid = "LuminateZenDen";
char* password = "123456789";

Lumistick lumistick;
  
String client_type ="WiFi";
byte brightness = 200;
byte saturation = 200;
    
void setup() {
    lumistick.initiate_stick(client_type, ssid, password);
}

void loop() {
  while (lumistick._clienton == 0) {
    lumistick.clrs(0, brightness, saturation);
  }
}
