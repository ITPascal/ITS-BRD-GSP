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
void initLEDs(const uint8_t val);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion setzt die ERROR LED
 *
 *  @return     void
 ****************************************************************************************/
void setErrorLED(bool on);

/*
 ****************************************************************************************
 *  @brief      Diese LED zeigt an das es vorwärts sich dreht.
 *
 *  @return     void
 ****************************************************************************************/
void setForwardLED(bool on);

/*
 ****************************************************************************************
 *  @brief      Diese LED zeigt an das es rückwärts sich dreht.
 *
 *  @return     void
 ****************************************************************************************/
void setBackwardLED(bool on);

/*
 ****************************************************************************************
 *  @brief      Diese LED1 zur Zeitmessung
 *
 *  @return     void
 ****************************************************************************************/
void setLEDTime(bool on);

/*
 ****************************************************************************************
 *  @brief      Diese LED2 zur Zeitmessung
 *
 *  @return     void
 ****************************************************************************************/
void setLEDTime2(bool on);
#endif
// EOF
