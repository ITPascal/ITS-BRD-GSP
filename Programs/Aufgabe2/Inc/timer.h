/**
  * @file timer.h
  * @author Julius Sawilski 
  * @date Nov 25
  * @brief Header file of timer module  
  */

#ifndef TIMER_H
#define TIMER_H
#include <stdbool.h>

/*
 ****************************************************************************************
 *  @brief      This function initialize the timer
 *
 *  @return     0 if initializing was successfull. Otherwise ...
 ****************************************************************************************/
int initTimer(void);

/*
 ****************************************************************************************
 *  @brief      This function returns a the current Timervalue
 *
 *  @return     0 if writing timestamp was successfull. Otherwise ...
 ****************************************************************************************/
int getTimeStamp(int *timestmp);

#endif /* OUTPUT_H */
// EOF
