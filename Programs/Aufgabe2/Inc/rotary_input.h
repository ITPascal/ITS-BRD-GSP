/**
  * @file rotary_input.h
  * @author Julius Sawilski 
  * @date Nov 2025
  * @brief Header file of input module. 
  */

#ifndef ROTARY_INPUT_H
#define ROTARY_INPUT_H

#include <stdint.h>
/*
 ****************************************************************************************
 *  @brief      This function initialize the input function.
 *
 *  @return     void 
 ****************************************************************************************/

void initInput(void);
int readInput(uint32_t *in); 
#endif 
// EOF
