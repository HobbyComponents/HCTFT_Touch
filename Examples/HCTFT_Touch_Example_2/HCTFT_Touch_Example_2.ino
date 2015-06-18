/* FILE:    HCTFT_Touch_Example_2
   DATE:    17/06/145
   VERSION: 0.1
   AUTHOR:  Andrew Davies

   
This example will display information from the touch screen library directly to
your display. This example will require the HCTFT library to be installed in 
addition to the HCTFT_Touch library.

To use this sketch you will need to uncomment the appropriate initialisers below
for your particular display.

IF YOU GET AN OUT OF MEMRY COMPILE ERROR:
Library support for TFT screens can be quite memory intensive. If you are using 
an UNO you may find that you will get and out of memory compile error. To get the
sketch to compile you will need to edit the MemorySave.h file in the HCTFT folder
to free up some memory.


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

/* Include the HCTFT and HCTOUCH libraries */
#include "HCTFT.h"
#include "HCTFT_Touch.h"
#include "SPI.h"


/* Uncomment one of the lines below to to create an instance of the TFT library 
   to match your screen */
//HCTFT HCTFT(ELECFREAKS_2_4_WITH_TFT01_UNO); // Elecfreaks 2.4" TFT (HCARDU0083)
//HCTFT HCTFT(ELECFREAKS_3_2_WITH_TFT01_MEGA); // Elecfreaks 3.2" TFT (HCARDU0097)
//HCTFT HCTFT(MCUFRIEND_3_5_MEGA); // Mcufriend 3.5" TFT (HCARDU0096)


/* Uncomment one of the lines below to to create an instance of the TFT_Touch 
   library to match your screen */
//HCTFT_Touch Touch(ELECFREAKS_2_4_WITH_TFT01_UNO); // Elecfreaks 2.4" TFT (HCARDU0083)
//HCTFT_Touch Touch(ELECFREAKS_3_2_WITH_TFT01_MEGA); // Elecfreaks 3.2" TFT (HCARDU0097)
//HCTFT_Touch Touch(MCUFRIEND_3_5_MEGA); // Mcufriend 3.5" TFT (HCARDU0096)


void setup() 
{
  /* Initialise the TFT library */
  HCTFT.Init();
}

/* Main sketch */
void loop() 
{
  int X_RawData;
  int Y_RawData;
  int X_Coord;
  int Y_Coord;
  
  /* Display some instructions to the screen */
  DisplayInstructions();

  while(1)
  {
    /* Check if the touch screen is currently pressed */
    if(Touch.Pressed())
    {
      /* Read the raw data for the X and Y axis */
      Y_RawData = Touch.ReadAxis(YAXIS);
      X_RawData = Touch.ReadAxis(XAXIS);
    
      /* Read the current X and Y axis as pixel co-ordinates */
      Y_Coord = Touch.GetCoord(YAXIS);
      X_Coord = Touch.GetCoord(XAXIS);
    
      HCTFT.Erase(200,80,280,118);
    
      /* Display the raw coordinates */
      HCTFT.SetFG(SILVER);
      HCTFT.SetFont(Terminal_8pt);
      HCTFT.Scale(2);
      HCTFT.Cursor(5, 80);
      HCTFT.Print("RAW X axis: ");
      HCTFT.Print(X_RawData);
      HCTFT.Cursor(5, 100);
      HCTFT.Print("RAW Y axis: ");
      HCTFT.Print(Y_RawData);
      
      /* Display the pixel coordinates */
      HCTFT.SetFG(MAROON);
      HCTFT.SetFont(LCDLarge_24pt);   
      HCTFT.Erase(60,170,140,220);
      HCTFT.Cursor(60, 170);
      HCTFT.Print(X_Coord);
      HCTFT.Erase(190,170,270,220);
      HCTFT.Cursor(190, 170);
      HCTFT.Print(Y_Coord);
    }
  }
}


/* Display some information on the screen */
void DisplayInstructions(void)
{
  HCTFT.SetFG(BLUE);
  HCTFT.Rect(0,15,319,38,SOLID);
  
  HCTFT.SetFG(WHITE);
  HCTFT.SetFont(Terminal_8pt);
  HCTFT.Scale(2);
  HCTFT.Cursor(10, 20);
  HCTFT.Print("TOUCH SCREEN TEST");
  
  HCTFT.SetFG(BLACK);
  HCTFT.Scale(1);
  HCTFT.Cursor(1, 45);
  HCTFT.Print("Touch the screen to get the current");
  HCTFT.Cursor(10, 56);
  HCTFT.Print("coordinate as raw and pixel values");
  
  HCTFT.SetFG(GREEN);
  HCTFT.Scale(2);
  HCTFT.Cursor(5, 130);
  HCTFT.Print("X/Y AXIS IN PIXELS");
}
