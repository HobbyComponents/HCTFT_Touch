#ifndef HCTFT_Calibration_h
#define HCTFT_Calibration_h

/******************************************************************************
					 CALIBRATION SETTING FOR EACH SCREEN
					 
If you find that the library is giving inaccurate coordinates for your screen 
or is not sensing the edges of the screen area you can tweak the calibration 
settings below. You can use the example sketch(s) included with this library
to find the correct values for your screen. XMIN and YMIN values are for the 
top left hand corner of the screen. XMAX and YMAX are for the bottom right 
hand corner of the screen.

******************************************************************************/


/* CHANGE THESE VALUES IF YOU ARE USING THE ELEC FREAKS 2.4" TFT (HCARDU0083) */
#define ELECFREAKS_2_4_YMAX 320 /* Raw Y axis measurement for top of visible screen */
#define ELECFREAKS_2_4_YMIN 3800 /* Raw Y axis measurement for bottom of visible screen */
#define ELECFREAKS_2_4_XMAX 3870 /* Raw X axis measurement for right of visible screen */
#define ELECFREAKS_2_4_XMIN 400 /* Raw X axis measurement for left of visible screen */


/* CHANGE THESE VALUES IF YOU ARE USING THE MCU FRIEND 3.5" TFT (HCARDU0096) */
#define MCUFRIEND_3_5_YMAX 3860 /* Raw Y axis measurement for top of visible screen */
#define MCUFRIEND_3_5_YMIN 220 /* Raw Y axis measurement for bottom of visible screen */
#define MCUFRIEND_3_5_XMAX 400 /* Raw X axis measurement for right of visible screen */
#define MCUFRIEND_3_5_XMIN 3950 /* Raw X axis measurement for left of visible screen */


/* CHANGE THESE VALUES IF YOU ARE USING THE ELEC FREAKS 3.2" TFT (HCARDU0097) */
#define ELECFREAKS_3_2_YMAX 3800 /* Raw Y axis measurement for top of visible screen */
#define ELECFREAKS_3_2_YMIN 300 /* Raw Y axis measurement for bottom of visible screen */
#define ELECFREAKS_3_2_XMAX 3800 /* Raw X axis measurement for right of visible screen */
#define ELECFREAKS_3_2_XMIN 450 /* Raw X axis measurement for left of visible screen */

#endif