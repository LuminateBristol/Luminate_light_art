#include "WPSource.h"

int data_lows[] = {63, 239, 241, 248, 255, 249, 235, 66, 163, 166, 168, 167, 165, 131, 84, 181, 182, 186, 183, 180, 125, 91, 152, 151, 153, 152, 150, 101, 144, 245, 246, 252, 191, 37, 38, 134, 166, 166, 168, 107, 27, 55, 162, 180, 184, 185, 95, 21, 50, 143, 149, 152, 152, 62, 22, 76, 236, 235, 127, 34, 57, 158, 165, 106, 30, 68, 217, 235, 146, 40, 51, 150, 160, 112, 37, 45, 175, 232, 193, 56, 43, 129, 157, 149, 48, 34, 27, 56, 212, 227, 208, 73, 54, 122, 138, 73, 102, 194, 114, 100, 163, 150, 98, 140, 201, 110, 92, 157, 101, 27, 120, 96, 108, 115, 104, 86, 68, 80, 133, 134, 140, 135, 75, 55, 112, 141, 140, 142, 128, 70, 51, 97, 122, 138, 133, 108, 50, 83, 93, 112, 122, 96, 127, 52, 63, 127, 129, 145, 139, 97, 36, 90, 140, 141, 149, 137, 84, 54, 71, 127, 129, 139, 136, 76, 38, 106, 112, 105, 112, 105, 82, 61, 96, 133, 138, 148, 126, 58, 42, 126};
int data_meds[] = {};
int data_highs[] = {10, 0, 0, 6, 0, 0, 8, 0, 0, 0, 31, 0, 0, 13, 15, 0, 10, 11, 0, 0, 30, 0, 0, 14, 0, 0, 0, 57, 7, 17, 0, 24, 6, 11, 16, 0, 18, 5, 0, 9, 16, 19, 16, 10, 11, 5, 15, 0, 38, 19, 0, 23, 10, 14, 44, 39, 16, 17, 28, 42, 23, 1, 21, 26, 56, 28, 27, 5, 72, 10, 42, 53, 92, 26, 2, 83, 84, 40, 110, 51, 35, 19, 127, 75, 164, 26, 79, 52, 77, 105, 92, 100, 150, 155, 155, 91, 221, 117, 234, 138, 85, 136, 255, 139, 105, 97, 134, 57, 87, 13, 16, 21, 9, 16, 18, 2, 14, 7, 23, 11, 18, 18, 3, 15, 6, 18, 18, 8, 15, 1, 14, 8, 21, 16, 10, 15, 1, 12, 15, 9, 16, 8, 12, 1, 12, 17, 12, 15, 11, 11, 9, 5, 13, 9, 14, 8, 9, 8, 5, 16, 11, 14, 14, 2, 8, 5, 13, 9, 12, 11, 1, 6, 7, 16, 14, 11, 13, 3, 7, 7};

int time_int = 500; // Time interval of must be the same as the time interval of the arrays above (from Python script)
int time_steps = 900;
int drop_time = 45000;
unsigned long timenow;
unsigned long timethen = 0;
unsigned long start_time;
int ind;

int low_pixel_one;
int low_pixel_two;
int high_pixel_one;
int high_pixel_two;

int peace_colour = 1;
int colour_int;

void setup() {
  ringleds.initLED();
  Serial.begin(9600);
  flashthree();
  start_time = millis();
}

void loop() {
  timenow = millis();
  if (timenow > timethen + time_int) {
    ind = int((timenow - start_time) / time_int); // Find the correct array index based on time 
    light_lows(ind);
    //light_highs(ind);
    timethen = timenow;
    Serial.println(timenow - start_time);
    Serial.println(ind);
    Serial.println(colour_int);
    Serial.println("");
  }
  
  if (timenow - start_time >= 90000) {
    ring_reset();
  }
}

/* Function 1: Turn on the LEDs related to low frequency sounds */
void light_lows(int i) {
  
  if (timenow - start_time < drop_time) {
    int thresh_low = 100; // If data is less than thresh, switch to new location on the ring 
    
    if (data_lows[i] < thresh_low) {
      ringleds.multioff(low_pixel_one, low_pixel_two);  
      colour_int = random(0, 255);  // Random colour choice - HSV spectrum
      low_pixel_one = random(0, NUM_LEDS);
      low_pixel_two = low_pixel_one + 15;
    }
    ringleds.setmulti(low_pixel_one, low_pixel_two, colour_int, data_lows[i]);
    
  } else {
    ringleds.setall(0, 200);
  }   
}

/* Function 2: Turn on the LEDs related to high frequency sounds */
void light_highs(int i) {
    int thresh_high = 10; // If data is less than thresh, switch to new location on the ring
    int colour_int = 140; // Light blue
    if (data_highs[i] < thresh_high) {  
      high_pixel_one = random(0, NUM_LEDS);
      high_pixel_two = high_pixel_one + 2;
    }
    ringleds.setmulti(high_pixel_one, high_pixel_two, colour_int, data_highs[i]);
}

/* Function 3: When the sh*tstorm is over, we have peace and calm */
void peaceandcalm() {
  int t = 100;
  if (timenow > timethen + t) {
    if (peace_colour < 255) {
      peace_colour++;
    } else {
      peace_colour--;
    }
    ringleds.setall(peace_colour, 200);
  }
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
