/* FILE:    HCTFT_Touch.h
   DATE:    10/06/14
   VERSION: 0.2
   AUTHOR:  Andrew Davies

   
V0.2 (17/06/15): Updated to work with MCUFriend 3.5" (HCARDU0096) & 
                 Elec Freaks 3.2" (HCARDU0097) screens.    
   
Library for TFT touch screens.

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

#ifndef HCTFT_Touch_h
#define HCTFT_Touch_h

#include "Arduino.h"
#include "HCTFT_Calibration.h"


#define MCUFRIEND_3_5_MEGA 0 // 3.5" TFT display for Arduino Mega (HCARDU0096)
#define ELECFREAKS_3_2_WITH_TFT01_MEGA 1 // 3.2" TFT screen for Arduino Mega (HCARDU0097)
#define ELECFREAKS_2_4_WITH_TFT01_UNO 2 // 2.4" TFT screen for Arduino Uno (HCARDU0083)


#define YAXIS 1
#define XAXIS 0

#define TOUCH_MINX pgm_read_word_near(&TOUCH_MIN_X[_Display])
#define TOUCH_MAXX pgm_read_word_near(&TOUCH_MAX_X[_Display])
#define TOUCH_MINY pgm_read_word_near(&TOUCH_MIN_Y[_Display])
#define TOUCH_MAXY pgm_read_word_near(&TOUCH_MAX_Y[_Display])


class HCTFT_Touch
{
	public:
	HCTFT_Touch(byte DisplayType);
	HCTFT_Touch(byte CS_Pin, byte Clk_Pin, byte Din_DIO, byte Dout_DIO);
	int ReadAxis(boolean Axis);
	int GetCoord(boolean Axis);
	boolean Pressed(void);
  
	private:
	byte _CS;
	byte _Clk;
	byte _Din;
	byte _Dout;
	void _PulseClock(void);
	int _ReadData(void);
	void _OutputData(byte Data);
	byte _Display;
};

#endif