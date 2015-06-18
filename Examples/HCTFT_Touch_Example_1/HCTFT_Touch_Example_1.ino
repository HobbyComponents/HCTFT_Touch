/* FILE:    HCTFT_Touch_Example_1
   DATE:    10/06/14
   VERSION: 0.2
   AUTHOR:  Andrew Davies
   
   V0.2 (17_06_2015): Updated for our latest TFT displays (HCARDU0097 & HCARDU0096)

This is an example of how to use the HCTFT_Touch library. The library provides the 
ability to read the current status of the touch screen. It does not provide any 
functions for controlling the TFT screen itself but is intended for providing touch 
screen support to any existing sketches or libraries. However the library will work 
standalone as this example sketch will demonstrate.

The example will read the current state of the touch screen and output it to the serial
port as raw X and Y coordinates, and as the current position in pixels. No information 
will be displayed on the TFT screen itself whilst this example is running.

To use this sketch you will need to uncomment the appropriate initialiser below for 
your particular display.

You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/

#include <HCTFT_Touch.h>

/* Uncomment one of the lines below to to create an instance of the TFT_Touch 
   library to match your screen */
//HCTFT_Touch Touch(ELECFREAKS_2_4_WITH_TFT01_UNO); // Elecfreaks 2.4" TFT (HCARDU0083)
//HCTFT_Touch Touch(ELECFREAKS_3_2_WITH_TFT01_MEGA); // Elecfreaks 3.2" TFT (HCARDU0097)
//HCTFT_Touch Touch(MCUFRIEND_3_5_MEGA); // Mcufriend 3.5" TFT (HCARDU0096)


void setup() 
{
  Serial.begin(9600);
}

/* Main program */
void loop()
{
  int X_RawData;
  int Y_RawData;
  int X_Coord;
  int Y_Coord;
  
  /* Check if the touch screen is currently pressed */
  if(Touch.Pressed())
  {
    /* Read the raw data for the X and Y axis */
    Y_RawData = Touch.ReadAxis(YAXIS);
    X_RawData = Touch.ReadAxis(XAXIS);
    
    /* Read the current X and Y axis as pixel co-ordinates */
    Y_Coord = Touch.GetCoord(YAXIS);
    X_Coord = Touch.GetCoord(XAXIS);

    /* Output the results to the serial port */
    Serial.print(Y_RawData);
    Serial.print(" : ");
    Serial.print(X_RawData);
    Serial.print(" : ");    
    Serial.print(Y_Coord);
    Serial.print(" : ");
    Serial.println(X_Coord);
    delay(100);
  }
}
