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
/*
 ****************************************************************************************
 *  @brief      This function up updates the internal char-buffer for the current speed and
 *              angle and updates the next char of angle and speed
 *
 *  @param      double angle  current angle to be printed
 *              double speed  current speed to be printed
 ****************************************************************************************/
void updateDisplay(double angle, double anglePerSec);

#endif
// EOF