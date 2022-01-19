#include "WPSource.h"

int Blue = 160;

void setup() {
  leds.initLED();
}

void loop() {
  leds.setall(Blue);
}
