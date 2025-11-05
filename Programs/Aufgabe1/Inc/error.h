/**
 ******************************************************************************
 * @file    error.h
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor f�r technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    17. Juli 2020
 * @brief   Einfache Error Handler, der User LED1 und LED2 blinken laesst.
 ******************************************************************************
 */
 
/**
  * @brief Einfacher Error Handler, der in einer Endlosschleife 
	*        die LEDs LED1 und LED2 blinken laesst.
  * @param  None
  * @retval None
  */

#ifndef _ERROR_H
#define	_ERROR_H

#define ERR_OVERFLOW   -1
#define ERR_UNDERFLOW  -2
#define ERR_DIVZERO    -3
#define ERR_STACKEMPTY -4
#define ERR_UNKNOWN    -99

extern void handleError(int v);

#endif

// EOF