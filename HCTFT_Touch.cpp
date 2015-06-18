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


#include "Arduino.h"
#include "HCTFT_Touch.h"
#include <avr/pgmspace.h>

/* Control pin mappings for each display type */
const PROGMEM byte CS[] = {5,5,8};
const PROGMEM byte CLK[] = {6,6,15};
const PROGMEM byte DIN[] = {4,4,14};
const PROGMEM byte DOUT[] = {3,3,9};

/* Screen resolutions */
const PROGMEM unsigned int MAX_X[] = {479,319,319};
const PROGMEM unsigned int MAX_Y[] = {319,239,239};

/* Touch screen calibrations */
const PROGMEM unsigned int TOUCH_MIN_X[] = {MCUFRIEND_3_5_XMIN, ELECFREAKS_3_2_XMIN,ELECFREAKS_2_4_XMIN};
const PROGMEM unsigned int TOUCH_MAX_X[] = {MCUFRIEND_3_5_XMAX, ELECFREAKS_3_2_XMAX,ELECFREAKS_2_4_XMAX};
const PROGMEM unsigned int TOUCH_MIN_Y[] = {MCUFRIEND_3_5_YMIN, ELECFREAKS_3_2_YMIN,ELECFREAKS_2_4_YMIN};
const PROGMEM unsigned int TOUCH_MAX_Y[] = {MCUFRIEND_3_5_YMAX, ELECFREAKS_3_2_YMAX,ELECFREAKS_2_4_YMAX};


/* Constructor to initialise the GPIO */
HCTFT_Touch::HCTFT_Touch(byte DisplayType)
{
	_Display = DisplayType;
	_CS = pgm_read_byte_near(&CS[_Display]);
	_Clk = pgm_read_byte_near(&CLK[_Display]);
	_Din = pgm_read_byte_near(&DIN[_Display]);
	_Dout = pgm_read_byte_near(&DOUT[_Display]);

	pinMode(_CS, OUTPUT); 
	pinMode(_Clk, OUTPUT); 
	pinMode(_Din, OUTPUT); 
	pinMode(_Dout, INPUT); 
  
	digitalWrite(_CS, HIGH);  
	digitalWrite(_Clk, LOW);
	digitalWrite(_Din, LOW);
}

/* Old constructor to maintain compatibility. May get removed at some point. */
HCTFT_Touch::HCTFT_Touch(byte CS_Pin, byte Clk_Pin, byte Din_Pin, byte Dout_Pin)
{
	_Display = ELECFREAKS_2_4_WITH_TFT01_UNO;
	_CS = CS_Pin;
	_Clk = Clk_Pin;
	_Din = Din_Pin;
	_Dout = Dout_Pin;

	pinMode(_CS, OUTPUT); 
	pinMode(_Clk, OUTPUT); 
	pinMode(_Din, OUTPUT); 
	pinMode(_Dout, INPUT); 
  
	digitalWrite(_CS, HIGH);  
	digitalWrite(_Clk, LOW);
	digitalWrite(_Din, LOW);
}


/* Detects if the touch screen is currently pressed. Returns TRUE if pressed */
boolean HCTFT_Touch::Pressed(void)
{
	int Y_Data;
	int X_Data;
	int CalMinX, CalMaxX, CalMinY, CalMaxY;
  
	//Save the calibration values for the selected display depending high and low values */
	if(TOUCH_MAXX > TOUCH_MINX)
	{
		CalMinX = TOUCH_MINX;
		CalMaxX = TOUCH_MAXX;
	}else
	{
		CalMaxX = TOUCH_MINX;
		CalMinX = TOUCH_MAXX;
	}

	if(TOUCH_MAXY > TOUCH_MINY)
	{
		CalMinY = TOUCH_MINY;
		CalMaxY = TOUCH_MAXY;
	}else
	{
		CalMaxY = TOUCH_MINY;
		CalMinY = TOUCH_MAXY;
	}
  
 
	/* Read the touch sensor */
	Y_Data = ReadAxis(YAXIS);
	X_Data = ReadAxis(XAXIS);
 
	/* If reading is within the calibrated area then screen has been pressed */
	if((Y_Data >= CalMinY && Y_Data <= CalMaxY) && (X_Data >= CalMinX && X_Data <= CalMaxX))
	{
		return true; 
	}else
	{
		return false;
	}
}

/* Reads one of the axis (XAXIS or YAXIS) raw coordinates. */
int HCTFT_Touch::ReadAxis(boolean Axis)
{
	int Data;
  
	/* Axis for 3.5" MCUFriend screen is flipped */
	if (_Display == MCUFRIEND_3_5_MEGA)
		Axis = !Axis;
  
	/* Read one of the axis */
	digitalWrite(_CS, LOW);
	if (Axis)
	{
		_OutputData(0xD0);   
	}else
	{
		_OutputData(0x90);
	}

	_PulseClock();
	Data = _ReadData();
	_PulseClock();
	_PulseClock();
	_PulseClock();
	digitalWrite(_CS, HIGH); 
	digitalWrite(_Din, LOW);
  
	return Data;
}

/* Generates a pulse on the clock pin */
void HCTFT_Touch::_PulseClock(void)
{
	digitalWrite(_Clk, HIGH);
	digitalWrite(_Clk, LOW);
}

/* Reads the raw data from the touch screen */
int HCTFT_Touch::_ReadData(void)
{
	byte index;
	int Data;
	Data = 0;
	for (index = 12; index > 0; index--)
	{
		Data += digitalRead(_Dout) << (index-1);
		_PulseClock();
	}
	return Data;
}  

/* Writes to the touch screen's configuration register */
void HCTFT_Touch::_OutputData(byte Data)
{
	byte index;
  
	for (index = 8; index > 0; index--)
	{
		digitalWrite(_Din, (Data >> (index -1)) & 1);
		_PulseClock();
	}
}

/* Read the current position from the touch screen and return it as a pixel position. */
int HCTFT_Touch::GetCoord(boolean Axis)
{
	unsigned int Axis_Data;
	unsigned int Coord;
	unsigned int ResX = pgm_read_word_near(&MAX_X[_Display]);
	unsigned int ResY = pgm_read_word_near(&MAX_Y[_Display]);

	Axis_Data = ReadAxis(Axis);
  
	if(Axis)
	{

		Coord = constrain(map(Axis_Data, TOUCH_MINY, TOUCH_MAXY, 0, ResY), 0, ResY);
	}else
	{
		Coord = constrain(map(Axis_Data, TOUCH_MINX, TOUCH_MAXX, 0, ResX), 0, ResX);
	}
  
  return Coord;
}