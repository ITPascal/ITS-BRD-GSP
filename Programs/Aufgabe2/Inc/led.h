/**
  * @file led.h
  * @author Julius Sawilski 
  * @date Nov 25
  * @brief Header file of led module  
  */

#ifndef LED_H
#define LED_H
#include <stdbool.h>

/*
 ****************************************************************************************
 *  @brief      This function initialized the LEDs
 * 
 *  @return     0 if setting initializing was successfull. Otherwise ...
 ****************************************************************************************/
int initLEDs(void);

/*
 ****************************************************************************************
 *  @brief      This function displays the counter using dedicated LEDs 
 *
 *  @return     0 if displaying was successfull. Otherwise ...
 ****************************************************************************************/
int showCounter(void);

/*
 ****************************************************************************************
 *  @brief      This function displays the direction of the rotation using dedicated LEDs
 *
 *  @return     0 if displaying was successfull. Otherwise ...
 ****************************************************************************************/
int showDirection(void);

/*
 ****************************************************************************************
 *  @brief      This function displays that an error has occurred using dedicated LEDs
 *
 *  @return     0 if displaying was successfull. Otherwise ...
 ****************************************************************************************/
int showError(void);

/*
 ****************************************************************************************
 *  @brief      This function clears the LEDs dedicated to singaling errors
 *
 *  @return     0 if clearing was successfull. Otherwise ...
 ****************************************************************************************/
int clearErrorLED(void);
#endif /* OUTPUT_H */
// EOF
