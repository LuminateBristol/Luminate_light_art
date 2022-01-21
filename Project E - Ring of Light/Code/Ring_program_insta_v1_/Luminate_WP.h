/*
 * Title: Library file for Luminate_WP sessions
 * Version: v1
 * Date: January 2022
 * Purpose: Provide simplified control of LED lights based on the FastLED library
 * 
 * Author: Henry Hickson
 */

 #ifndef _Luminate_WP_h
 #define _Luminate_WP_h

 #include "FastLED.h"

 class Luminate_WP {
  public:
    #define NUM_LEDS 140
    #define LED_PIN 5
    CRGB leds[NUM_LEDS];
    byte saturation = 230;

    /* Function 1: Constructor */
  
    Luminate_WP() {
    }

    /* Function 2: Initiate the LEDs using the FastLED library */
 
    void initLED() {
      pinMode(LED_PIN, OUTPUT);
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    }

    /* Function 3: Set all LEDs to a colour */
  
    void setall(byte colour_int, byte brightness) {
      fill_solid(leds, NUM_LEDS, CHSV(colour_int, saturation, brightness));
      FastLED.show();
    }  

    /* Function 4: Turn off all LEDs */

    void alloff() {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
    }

    /* Function 5: Set one pixel to a colour */

    void setone(byte pixel_number, byte colour_int, byte brightness) {
      leds[pixel_number] = CHSV(colour_int, brightness, saturation);
      FastLED.show();
    }

    /* Function 6: Turn off one pixel */

    void oneoff(byte pixel_number) {
      leds[pixel_number] = CRGB::Black;
      FastLED.show();
    }

    /* Function 7: Set multiple pixels to a colour */

    void setmulti(byte pixel_0, byte pixel_1, byte colour_int, byte brightness) {
      for (byte i = pixel_0; i <= pixel_1; i++) {
        leds[i] = CHSV(colour_int, brightness, saturation);
      }
      FastLED.show();
    }

    /* Function 8: Turn off multiple pixels */
    void multioff(byte pixel_0, byte pixel_1) {
      for (byte i = pixel_0; i <= pixel_1; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }

  };

 
 #endif
