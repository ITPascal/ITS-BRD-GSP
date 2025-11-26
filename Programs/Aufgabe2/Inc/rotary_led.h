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
void setLEDCounter(int phasencounter);

/*
 ****************************************************************************************
 *  @brief      Diese LED löscht die ErrorLED.
 *
 *  @return     void
 ****************************************************************************************/
void clearErrorLED();

/*
 ****************************************************************************************
 *  @brief      Diese LED zeigt die Richtung des Drehgebers an.
 *
 *  @return     void
 ****************************************************************************************/
void setLEDDirection(int state);

#endif
// EOF
