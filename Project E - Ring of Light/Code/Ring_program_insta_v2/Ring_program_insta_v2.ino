#include "Arduino.h"
#include "FastLED.h"
#include "Luminate_WP.h"

Luminate_WP ringleds;

byte data_lows[] = {9, 42, 67, 67, 117, 192, 224, 250, 248, 230, 234, 236, 229, 230, 227, 233, 234, 238, 239, 246, 243, 255, 251, 242, 231, 236, 240, 241, 235, 242, 234, 245, 244, 245, 156, 34, 47, 49, 74, 114, 143, 162, 159, 159, 158, 160, 157, 158, 160, 162, 161, 162, 158, 164, 160, 162, 160, 161, 159, 159, 157, 158, 157, 159, 158, 161, 158, 158, 127, 23, 40, 55, 55, 110, 143, 171, 178, 174, 174, 170, 174, 171, 174, 176, 176, 173, 182, 177, 181, 179, 178, 178, 177, 173, 172, 176, 172, 169, 172, 170, 174, 174, 178, 42, 33, 46, 45, 91, 115, 137, 148, 145, 146, 143, 144, 144, 144, 144, 146, 145, 148, 149, 146, 147, 144, 147, 149, 144, 144, 142, 143, 144, 143, 144, 144, 146, 145, 100, 39, 55, 89, 91, 109, 183, 218, 246, 236, 230, 232, 227, 227, 235, 235, 238, 244, 244, 247, 237, 244, 234, 237, 241, 246, 142, 49, 43, 44, 30, 29, 29, 20, 20, 38, 45, 58, 70, 115, 138, 159, 163, 158, 157, 160, 160, 159, 156, 158, 163, 159, 161, 163, 158, 164, 158, 164, 162, 160, 111, 43, 35, 34, 27, 22, 26, 23, 17, 35, 48, 72, 93, 113, 142, 166, 181, 174, 172, 174, 171, 170, 175, 172, 176, 179, 179, 176, 178, 180, 175, 178, 176, 175, 163, 56, 34, 27, 23, 24, 19, 14, 19, 21, 34, 47, 52, 86, 111, 136, 149, 146, 145, 142, 141, 143, 145, 144, 143, 145, 149, 144, 149, 144, 146, 149, 147, 143, 143, 58, 36, 33, 27, 24, 21, 22, 20, 18, 38, 48, 88, 92, 97, 176, 216, 245, 250, 244, 223, 221, 229, 227, 224, 228, 218, 77, 50, 37, 40, 42, 27, 29, 22, 24, 37, 55, 60, 96, 122, 151, 165, 160, 160, 157, 157, 160, 160, 159, 158, 163, 116, 33, 39, 33, 28, 29, 30, 23, 23, 37, 63, 96, 109, 158, 197, 215, 239, 231, 223, 227, 223, 223, 232, 223, 232, 133, 65, 46, 41, 54, 35, 37, 26, 23, 32, 52, 60, 76, 119, 141, 149, 155, 153, 154, 156, 155, 150, 151, 152, 157, 138, 48, 43, 40, 42, 30, 39, 26, 28, 21, 30, 58, 76, 107, 131, 180, 196, 224, 237, 218, 216, 221, 221, 215, 220, 221, 198, 72, 67, 47, 65, 49, 41, 40, 27, 33, 46, 60, 67, 108, 132, 158, 156, 149, 149, 147, 154, 152, 160, 146, 159, 155, 93, 50, 48, 49, 42, 40, 37, 31, 33, 31, 32, 33, 30, 23, 22, 21, 22, 18, 49, 87, 91, 137, 188, 216, 235, 242, 216, 203, 235, 229, 203, 235, 243, 210, 215, 96, 64, 90, 74, 64, 56, 41, 54, 51, 49, 65, 74, 81, 125, 147, 160, 165, 160, 146, 91, 100, 76, 76, 55, 79, 65, 58, 70, 96, 119, 146, 164, 186, 201, 195, 186, 142, 96, 104, 99, 106, 97, 102, 95, 93, 91, 127, 129, 163, 174, 187, 175, 178, 138, 129, 100, 103, 92, 93, 89, 94, 98, 115, 122, 151, 186, 196, 209, 205, 188, 163, 117, 104, 102, 106, 95, 85, 92, 82, 81, 101, 113, 140, 163, 170, 165, 153, 121, 71, 65, 72, 25, 13, 12, 9, 69, 118, 153, 133, 97, 74, 58, 69, 95, 111, 129, 119, 88, 83, 115, 113, 97, 119, 134, 117, 85, 78, 77, 104, 106, 131, 120, 98, 99, 52, 46, 78, 84, 67, 51, 45, 45, 55, 77, 95, 112, 122, 139, 128, 132, 117, 109, 119, 124, 139, 149, 128, 139, 133, 143, 129, 128, 155, 131, 131, 101, 88, 81, 84, 49, 59, 58, 27, 23, 64, 93, 83, 92, 113, 119, 130, 141, 133, 138, 137, 127, 122, 137, 140, 140, 133, 152, 145, 139, 130, 112, 137, 143, 150, 109, 75, 77, 75, 76, 47, 60, 60, 54, 47, 42, 40, 55, 85, 96, 107, 123, 123, 123, 127, 108, 103, 115, 133, 143, 130, 139, 114, 148, 121, 123, 131, 136, 121, 104, 75, 81, 65, 66, 37, 40, 30, 19, 19, 97, 142, 121, 106, 108, 78, 54, 100, 102, 133, 130, 91, 83, 101, 115, 100, 121, 148, 114, 101, 74, 75, 95, 105, 127, 136, 134, 108, 51, 32, 47, 45, 72, 31, 52, 68, 64, 88, 104, 123, 126, 133, 124, 132, 127, 112, 116, 134, 144, 137, 141, 141, 134, 134, 131, 128, 139, 134, 133, 95, 102, 78, 56, 48, 51, 32, 22, 22, 52, 82, 113, 92, 94, 116, 131, 140, 149, 133, 142, 129, 118, 134, 153, 149, 141, 127, 154, 143, 126, 116, 129, 145, 140, 133, 121, 77, 45, 25, 49, 69, 66, 49, 26, 50, 54, 58, 80, 99, 116, 121, 124, 119, 130, 113, 103, 118, 140, 143, 130, 138, 135, 118, 145, 128, 121, 150, 130, 125, 86, 93, 65, 58, 62, 46, 28, 19, 13, 74, 117, 127, 103, 84, 75, 72, 103, 103, 125, 135, 100, 80, 101, 111, 111, 115, 128, 126, 90, 78, 61, 93, 101, 120, 128, 107, 93, 55, 52, 85, 69, 78, 55, 42, 48, 49, 72, 98, 115, 126, 129, 129, 132, 135, 115, 113, 132, 146, 139, 131, 152, 138, 150, 128, 140, 123, 141, 134, 100, 104, 90, 64, 41, 43, 41, 29, 23, 42, 54, 54, 82, 130, 129, 130, 133};
byte data_meds[] = {};
byte data_highs[] = {37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 34, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 4, 0, 0, 0, 33, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 36, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 25, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 19, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 59, 37, 66, 60, 15, 7, 3, 1, 1, 0, 21, 44, 0, 0, 0, 0, 0, 0, 0, 0, 53, 7, 0, 33, 21, 0, 0, 0, 0, 0, 0, 0, 0, 42, 2, 0, 50, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 66, 3, 0, 0, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 8, 49, 5, 0, 0, 27, 46, 1, 0, 1, 1, 0, 0, 53, 8, 0, 0, 0, 0, 40, 42, 0, 0, 0, 0, 0, 0, 16, 2, 0, 53, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 2, 70, 3, 1, 0, 26, 31, 18, 0, 0, 0, 0, 0, 0, 86, 2, 0, 0, 0, 0, 0, 0, 36, 52, 1, 0, 0, 0, 136, 3, 0, 0, 30, 70, 27, 16, 11, 26, 57, 2, 1, 0, 0, 65, 1, 0, 0, 0, 89, 21, 0, 0, 0, 0, 0, 0, 43, 120, 4, 2, 2, 73, 8, 1, 1, 1, 0, 0, 0, 0, 0, 79, 1, 1, 1, 93, 6, 1, 64, 14, 1, 57, 85, 44, 3, 49, 6, 9, 9, 3, 78, 15, 1, 1, 1, 2, 1, 13, 79, 3, 9, 157, 32, 20, 11, 5, 3, 1, 1, 1, 86, 72, 4, 5, 51, 101, 48, 1, 1, 126, 108, 5, 119, 21, 57, 19, 2, 2, 2, 2, 1, 1, 1, 120, 73, 4, 6, 122, 84, 26, 63, 82, 74, 4, 70, 3, 3, 75, 189, 62, 156, 19, 1, 37, 12, 1, 34, 117, 2, 3, 3, 116, 11, 7, 9, 46, 6, 4, 134, 79, 103, 118, 63, 9, 109, 3, 92, 79, 185, 90, 216, 28, 121, 30, 2, 26, 39, 3, 4, 4, 82, 124, 95, 4, 4, 55, 104, 36, 118, 83, 43, 52, 3, 82, 91, 33, 55, 150, 10, 4, 163, 40, 142, 112, 75, 56, 54, 94, 4, 90, 196, 94, 200, 114, 155, 67, 122, 148, 144, 160, 122, 27, 154, 174, 11, 41, 43, 86, 137, 188, 233, 204, 100, 105, 96, 63, 64, 128, 198, 100, 234, 170, 211, 170, 143, 44, 56, 125, 41, 63, 84, 129, 15, 81, 86, 85, 48, 230, 249, 255, 201, 145, 146, 145, 124, 86, 84, 103, 86, 136, 27, 105, 57, 79, 76, 30, 75, 118, 60, 143, 123, 101, 95, 51, 45, 35, 40, 53, 82, 86, 84, 78, 9, 46, 3, 1, 0, 2, 34, 16, 3, 4, 5, 6, 6, 57, 7, 7, 7, 6, 7, 7, 7, 32, 14, 6, 6, 6, 6, 6, 6, 6, 45, 4, 1, 1, 1, 1, 1, 1, 22, 28, 2, 3, 4, 5, 6, 8, 8, 50, 11, 10, 9, 9, 8, 9, 9, 8, 35, 9, 9, 9, 8, 8, 9, 9, 37, 8, 3, 2, 2, 2, 2, 2, 2, 49, 4, 3, 3, 4, 5, 6, 6, 33, 15, 7, 7, 7, 6, 8, 6, 6, 45, 7, 6, 7, 6, 5, 6, 6, 22, 22, 2, 2, 1, 1, 1, 1, 1, 43, 6, 3, 3, 4, 5, 7, 8, 9, 46, 10, 10, 9, 9, 9, 9, 9, 27, 10, 8, 8, 8, 8, 8, 8, 8, 37, 4, 2, 1, 1, 1, 1, 1, 28, 12, 2, 3, 3, 4, 5, 6, 6, 40, 7, 7, 7, 7, 7, 7, 6, 21, 23, 7, 6, 7, 6, 6, 6, 6, 36, 4, 2, 1, 1, 1, 1, 1, 1, 34, 2, 3, 4, 5, 6, 8, 8, 33, 12, 10, 9, 8, 9, 9, 9, 9, 24, 8, 9, 8, 8, 8, 9, 8, 24, 11, 4, 3, 2, 2, 2, 2, 2, 28, 4, 3, 3, 3, 4, 5, 6, 16, 16, 7, 7, 7, 6, 7, 7, 7, 29, 8, 6, 7, 6, 5, 6, 6, 6, 30, 2, 2, 1, 1, 1, 1, 1, 23, 5, 3, 3, 4, 5, 7, 8, 9, 26, 10, 10, 9, 8, 9, 9, 9, 21, 11, 8, 8, 8, 8, 8, 8, 8, 24, 4, 2, 1, 1, 1, 1, 1, 12, 16, 3, 3, 3, 4, 4, 5, 6, 23, 7, 7, 7, 7, 7, 7, 6, 7, 21, 6, 6, 7, 6, 6, 6, 6, 19, 5, 2, 1, 1, 1, 1, 1, 1, 18, 3, 3, 4, 4, 6, 7, 8, 22, 13, 10, 9, 9, 8, 9, 9, 9, 20, 8, 8, 8, 8, 8, 8, 8, 16, 15, 4, 3, 2, 2, 2, 2, 2, 15, 4, 3, 3, 4, 4, 5, 6, 6};

int time_int = 100; // Time interval of must be the same as the time interval of the arrays above (from Python script)
int time_steps = 900;
int drop_time = 55000;
unsigned long timenow;
unsigned long timethen = 0;
unsigned long start_time;
int ind;

byte low_pixel_one;
byte low_pixel_two;
byte high_pixel_one;
byte high_pixel_two;

int thresh_low = 80; // If data is less than thresh, switch to new location on the ring
int thresh_high = 10; // If data is less than thresh, switch to new location on the ring


byte colour_int;
int ltm;
int ltmold = 0;

void setup() {
  ringleds.initLED();
  Serial.begin(9600);
  flashthree();
  start_time = millis();
}

void loop() {
  
  timenow = millis();
  if (timenow > timethen + time_int) {
    if (timenow - start_time < drop_time) {  
      ind = int((timenow - start_time) / time_int); // Find the correct array index based on time 
      light_highs(ind);
      light_lows(ind);
      timethen = timenow;
      //Serial.println(timenow - start_time);
    } else {
      ind = int((timenow - start_time) / time_int); // Find the correct array index based on time 
      peaceandcalm(ind);
    }
  }
  
  if (timenow - start_time >= time_int*time_steps) {
    ring_reset();
  }
}

/* Function 1: Turn on the LEDs related to low frequency sounds */
void light_lows(int i) {    
    
    if (data_lows[i] > thresh_low) {     
      ltm = 1;
    }
    else if (data_lows[i] < thresh_low) {
      ltm = 0;
    }   
    int a = ltmold - ltm;
    ltmold = ltm;  
    if (a == 1) {         
      colour_int = random(0, 255);  // Random colour choice - HSV spectrum
    }    
    
    ringleds.setall(colour_int, data_lows[i]/3.5); 
}

/* Function 2: Turn on the LEDs related to high frequency sounds */
void light_highs(int i) { 
  if (data_highs[i] > thresh_high) {  
    high_pixel_one = random(0, NUM_LEDS);
    high_pixel_two = high_pixel_one + 5;
    ringleds.setmulti(high_pixel_one, high_pixel_two, 140, 250);
  }
  ringleds.setmulti(high_pixel_one, high_pixel_two, colour_int, data_lows[i]/3.5); // Revert previously turned on LEDs
}

/* Function 3: When the sh*tstorm is over, we have peace and calm */
void peaceandcalm(int i) {
  if (data_lows[i] > thresh_low) {     
      ltm = 1;
    }
    else if (data_lows[i] < thresh_low) {
      ltm = 0;
    }   
    int a = ltmold - ltm;
    ltmold = ltm;  
    if (a == 1) {         
      colour_int = colour_int+20;  // Random colour choice - HSV spectrum
    }    
    
    ringleds.setall(colour_int, data_lows[i]/2); 
}


/* Function 4: Reset the Ring to begninning, wait 2 seconds before restart */
void ring_reset() {
  delay(2000);
  flashthree();
  start_time = millis();
}

/* Function 5: Flash three times to show we are ready to start the program */
void flashthree() {
  ringleds.setall(0, 200);
  delay(500);
  ringleds.alloff();
  delay(500);
  ringleds.setall(0, 200);
  delay(500);
  ringleds.alloff();
  delay(500);
  ringleds.setall(0, 200);
  delay(500);
  ringleds.alloff();
  delay(500);
}


/* Code Explanation:

So we have our results in 1/10 second chunks = 100ms.

Using the millis() command we could say that the brightness for different pixles should be set,
but the risk with this is that we would miss commands if set them to occur on a given time signature.

The solution I think is to set it such that commands run after 100ms intervals.

I.e. if starttime + millis() > 100, run light program for 100ms
     if starttime + millis() > 200, run light program for 200ms

There are three sets of data. Lets start with highs and lows and run programs for each of those.

Each 100ms we want to run the brightness of SOME pixels according to the data.

SOME pixels varies. For the highs - pick 2/3 pixels randomly everytime data < threshold_highs.

For lows pick increasing pixels starting at 5 and adding one each time. Random selection everytime data <
threshold_lows. For lows, the colours should also vary randomly

Then when we get to the drop, we want darkness followed by a nice colourful light routine.

*/
