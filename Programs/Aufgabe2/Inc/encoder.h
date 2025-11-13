/**
  * @file encoder.h
  * @author Julius Sawilski 
  * @date Nov 25
  * @brief Header file of encoder module  
  */

#ifndef ENCODER_H
#define ENCODER_H
#include <stdbool.h>

/*
 ****************************************************************************************
 *  @brief      This function initialize the encoder
 *
 *  @return     0 if initializing was successfull. Otherwise ...
 ****************************************************************************************/
int initEncoder(void);

/*
 ****************************************************************************************
 *  @brief      This function updates the encoder
 *
 *  @return     0 if updating was successfull. Otherwise ...
 ****************************************************************************************/
int updateEncoder(char c);

/*
 ****************************************************************************************
 *  @brief      This function writes the current encodeCount into count
 *
 *  @param      count int pointer to which the count is written
 *
 *  @return     0 if writing the count was successfull. Otherwise ...
 ****************************************************************************************/
int getEncoderCount(int *count);

/*
 ****************************************************************************************
 *  @brief      This function writes the current directing into direction
 *
 *  @param      direction int pointer to which the direction is written
 *
 *  @return     void 
 ****************************************************************************************/
int getDirection(int *direction);

/*
 ****************************************************************************************
 *  @brief      This informs the user if an error occurred
 *
 *  @return     void 
 ****************************************************************************************/
 int hasError();

#endif /* OUTPUT_H */
// EOF
