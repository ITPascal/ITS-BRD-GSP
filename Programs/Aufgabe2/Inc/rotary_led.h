/**
  * @file rotary_led.h
  * @author Julius Sawilski & Pascal Sendecky
  * @date Nov 25
  * @brief Header file of rotary_led module  
  */

#ifndef ROTARY_LED_H
#define ROTARY_LED_H

#include <stdbool.h>

/*
 ****************************************************************************************
 *  @brief      This function sets the ERROR LED.
 *
 *  @return     void
 ****************************************************************************************/
void setErrorLED(void);

/*
 ****************************************************************************************
 *  @brief      This functions displays the forward motion of the spinning object 
 *              using LEDs.
 *
 *  @return     void
 ****************************************************************************************/
void setLEDCounter(int phasencounter);

/*
 ****************************************************************************************
 *  @brief      This function clears the ERROR LED
 *
 *  @return     void
 ****************************************************************************************/
void clearErrorLED();

/*
 ****************************************************************************************
 *  @brief      This funtion displays the current direction using LEDs
 *
 *  @return     void
 ****************************************************************************************/
void setLEDDirection(int state);

#endif
// EOF
