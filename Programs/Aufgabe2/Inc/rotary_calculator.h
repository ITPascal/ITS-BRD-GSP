/**
  * @file rotary_calculator.h
  * @author Julius Sawilski & Pascal Sendecky
  * @date Nov 2025
  * @brief Header file of rotary_calculator module. 
  */

#ifndef ROTARY_RECHNER_H
#define ROTARY_RECHNER_H

#include <stdint.h>
/**
 * @brief masks the state the PHASE the State Machine was previously in.
 */
#define ORIG_PHASE_MASK 0x2
/**
 * @brief masks the PHASE the State Machine is in now.
 */
#define TRANS_PHASE_MASK 0x0
/**
 * @brief state in which the object is rotating forwards.
 */
#define STATE_FORWARD 1
/**
 * @brief state in which the object is rotating backwards.
 */
#define STATE_BACKWARDS 2
/**
 * @brief state in which the object has not undergone a phase change. 
          Occurs when the object is standing still, or has reentered 
          the current PHASE inbetween timestamps.
 */
#define STATE_NOCHANGE 3
/**
 * @brief state that occurs when no transition from the last PHASE 
          to the current PHASE is defined.
 */
#define STATE_ERROR 4
/*
 ****************************************************************************************
 *  @brief      This function determines the current state of the rotary encoder.
 *
 *  @param      uint32_t lastPhase  PHASE read before the currPhase
 *              uint32_t currPhase  the currently newest PHASE read
 *               
 *  @return     0 if successful. -1 otherwise 
 ****************************************************************************************/
int rotary_determineState(uint32_t lastPhase, uint32_t currPhase);

#endif /* OUTPUT_H */
// EOF
