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
 *  @brief      This function moves the cursor to the character that should be updated next.
                This is determined by their position (left to right).
 *
 *  @return     0 if successful. -1 otherwise 
 ****************************************************************************************/

 
int gotoNextChar(void);

/*
 ****************************************************************************************
 *  @brief      This function updates the char to which the cursor currently points.
                The char either belongs to the displayed speed value or to the angle
 *
 *  @return     0 if successful. -1 otherwise 
 ****************************************************************************************/

int updateChar(double speed, double angle);

#endif
// EOF