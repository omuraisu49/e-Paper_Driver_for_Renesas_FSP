/*****************************************************************************
 * File         :   Debug.h
 * Author       :   OMURAISU
 * Date         :   2021-01-30
 * Function     :   debug with printf
 * Info         :   Support Renesas Flexible Software Package (FSP)
 *                  This software is based on the following materials.
 *                  https://github.com/waveshare/e-Paper/tree/master/STM32
 *
 *                  Please refer to README.md for more detail/Usage info.
 *
 * The author(OMURAISU) does not take any responsibility caused by this material.
 * If you incorporate this material into your system, please be very careful.
 ****************************************************************************/
/*****************************************************************************
* | File      	:	Debug.h
* | Author      :   Waveshare team
* | Function    :	debug with printf
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __DEBUG_H
#define __DEBUG_H

#define DEBUG 0
#define PRINTF 0

#if DEBUG
	#define Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define Debug(__info,...)  
#endif

#if PINRTF == 0
    #define printf(__info,...)
#endif

#endif
