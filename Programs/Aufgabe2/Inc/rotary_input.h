/**
  * @file rotary_input.h
  * @author Julius Sawilski & Pascal Sendecky
  * @date Nov 2025
  * @brief Header file of rotary_input module. 
  *        provides the definition of the PHASEs returned. 
  */

#ifndef ROTARY_INPUT_H
#define ROTARY_INPUT_H

/**
 * @brief Phase bei PF1 = 0 und PF0 = 0.
 */
#define PHASE_A 0x00

/**
 * @brief Phase bei PF1 = 1 und PF0 = 0. 
 */
#define PHASE_B 0x10

/**
 * @brief Phase bei PF1 = 1 und PF0 = 1.
 */
#define PHASE_C 0x11

/**
 * @brief Phase bei PF1 = 0 und PF0 = 1. 
 */
#define PHASE_D 0x01
/*
 ****************************************************************************************
 *  @brief      This function initialize the input function.
 *
 *  @return     void 
 ****************************************************************************************/

void initInput(void);

/*
 ****************************************************************************************
 *  @brief      This function reads the pins PF0 and PF1. It writes the PHASE into in.
 *
 *  @return     input
 ****************************************************************************************/
int readInput(void); 

int buttonS6_pressed(void);

#endif 
// EOF
