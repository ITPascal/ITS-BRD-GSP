/**
  * @file rotary_led.h
  * @author Pascal Sendecky
  * @date Nov 25
  * @brief Header file of rotary_led module  
  */

#ifndef ROTARY_LED_H
#define ROTARY_LED_H

#include <stdbool.h>
#include <stdint.h>


/*
 ****************************************************************************************
 *  @brief      Diese Funktion initiallisiert die LEDs.
 * 
 *  @return     void
 ****************************************************************************************/
void initLEDs(void);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion setzt die ERROR LED
 *
 *  @return     void
 ****************************************************************************************/
void setErrorLED(void);

/*
 ****************************************************************************************
 *  @brief      Diese LED zeigt an das es vorwärts sich dreht.
 *
 *  @return     void
 ****************************************************************************************/
void setForwardLED(void);

/*
 ****************************************************************************************
 *  @brief      Diese LED zeigt an das es rückwärts sich dreht.
 *
 *  @return     void
 ****************************************************************************************/
void setBackwardLED(void);

#endif
// EOF
