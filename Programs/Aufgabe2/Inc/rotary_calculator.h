/**
  * @file rechner.h
  * @author Julius Sawilski 
  * @date Nov 2025
  * @brief Header file of encoder module. 
  */

#ifndef ROTARY_RECHNER_H
#define ROTARY_RECHNER_H

#include <stdint.h>
/**
 * @brief masks the state the PHASE the State Machine was previously in
 */
#define ORIG_PHASE_MASK 0x2
/**
 * @brief masks the PHASE the State Machine is in now
 */
#define TRANS_PHASE_MASK 0x0
/**
 * @brief state in which the object is rotating forwards
 */
#define STATE_FORWARD 1
/**
 * @brief state in which the object is rotating backwards
 */
#define STATE_BACKWARDS 2
/**
 * @brief state in which the object has not undergone a phase change. 
          Occurs when the object is standing still, or has reentered 
          the current PHASE inbetween timestamps
 */
#define STATE_NOCHANGE 3
/**
 * @brief state that occurs when no transition from the last PHASE 
          to the current PHASE is defined
 */
#define STATE_ERROR 4

int rotary_determineState(uint32_t lastPhase, uint32_t currPhase, int *newState);
int rotary_getAngle(double *angle, int steps, double anglePerStep);
int rotary_getSpeed(double *angle, int steps, double anglePerStep);
#endif /* OUTPUT_H */
// EOF
