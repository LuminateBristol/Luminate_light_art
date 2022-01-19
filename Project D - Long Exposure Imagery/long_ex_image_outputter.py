#Pixelate an image and output a multi-array to allow for
#long exposure imagery on the Lumistick
#HHickson March 2021

import cv2
import matplotlib.pyplot as plt
import mss
import numpy as np

#=====================================

#  Function Definitions

#=====================================
 
#Function to screenshot and pixelate the image based on the number of blocks specified by the ESP
def Pixelator(length, NUM_LEDS):
    
    #Read the image
    img = cv2.imread('/Users/henryhickson/Documents/Luminate/Light//Projects/Project D - Long Exposure Imagery/windows.png')
    img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB) #Correct colours in cv2
    
    #Resize the image to match the number of pixels in the size x*y LED matrix
    x = length
    y = NUM_LEDS
    pixels = cv2.resize(img,(x,y),interpolation = cv2.INTER_CUBIC)
    plt.imshow(pixels)
    plt.show()
    return(pixels);
    
#=====================================

#Function to convert the pixelated numpy array into one that can be read by Arduino
def convert_to_C_array(pixels, length, NUM_LEDS):
    
    print("{")
    for i in range(0,length):
        print("{", end="", flush=True)
        for j in range(0,NUM_LEDS):
            print(f'{{{pixels[j][i][0]},{pixels[j][i][1]},{pixels[j][i][2]}}}', end="", flush=True)
            if (j<NUM_LEDS-1):
                print(",", end="", flush=True)
            else:
                print("", end="", flush=True)
        print("}", end="", flush=True)
        if (i<length-1):
            print(",")
        else:
            print("")
    print("}")
      
#=====================================   

#RUN PROGRAM
     
#=====================================

def main():
    #Pixelate the image
    NUM_LEDS=5 #Height is the number of vertical pixels
    length=5 #Length is the number of longitudinal pixels
    pixels = Pixelator(length, NUM_LEDS)

    #Print out C version of the array
    convert_to_C_array(pixels, length, NUM_LEDS)
    
if __name__ == '__main__': main()
    


    

