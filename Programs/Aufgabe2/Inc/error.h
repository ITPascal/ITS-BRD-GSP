/**
  * @file error.h
  * @author Julius Sawilski 
  * @date Nov 25
  * @brief Header file of error module  
  */

#ifndef ERROR_H
#define ERROR_H
#include <stdbool.h>

/*
 ****************************************************************************************
 *  @brief      This function that sets the current error based on the errorcode argument
 * 
 *  @param      errorcode int to set as new current error
 *
 *  @return     0 if setting error was successfull. Otherwise ...
 ****************************************************************************************/
int setError(int errorcode);

/*
 ****************************************************************************************
 *  @brief      This function clears the current error
 *
 *  @return     0 if clearing was successfull. Otherwise ...
 ****************************************************************************************/
int clearError();

/*
 ****************************************************************************************
 *  @brief      This function checks if the value input corresponds to an error code
 *
 *  @param      v int value to check
 *
 *  @return     0 there is no correstsponding value, 1 if there is. Otherwise ...
 ****************************************************************************************/
int isError(int v);

#endif /* OUTPUT_H */
// EOF
