/**
  * @file rotary_display.h
  * @author Julius Sawilski 
  * @date Nov 2025
  * @brief Header file of rotary_display module. 
  */

#ifndef ROTARY_DISPLAY_H
#define ROTARY_DISPLAY_H
#include <stdbool.h>


/*
 ****************************************************************************************
 *  @brief      This function initializes the display for the rotary encoder.
 *
 *  @return     0 if successful. -1 otherwise 
 ****************************************************************************************/

void initDisplay(void);

void updateDisplay(double angle, double anglePerSec);

#endif
// EOF