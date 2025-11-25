/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "rotary_calculator.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "rotary_input.h"
#include "rotary_input.h"
#include "rotary_states.h"

#define PHASE_TRANSF(p1, p2) ((p1 << ORIG_PHASE_MASK) | (p2 << TRANS_PHASE_MASK))

int rotary_determineState(uint32_t lastPhase, uint32_t currPhase, int *newState) {

  switch(PHASE_TRANSF(lastPhase, currPhase)) {
    // originating from PHASE_A
    case PHASE_TRANSF(PHASE_A, PHASE_A): //A -> A
      *newState = STATE_NOCHANGE;
      break;
    case PHASE_TRANSF(PHASE_A, PHASE_B): //A -> B
      *newState = STATE_FORWARD;
      break;
    case PHASE_TRANSF(PHASE_A, PHASE_C): //A -> C
      *newState = STATE_ERROR;
      break;
    case PHASE_TRANSF(PHASE_A, PHASE_D): //A -> D
      *newState = STATE_BACKWARDS;
      break;
    // originating from PHASE_B
    case PHASE_TRANSF(PHASE_B, PHASE_A): //B -> A
      *newState = STATE_BACKWARDS;
      break;
    case PHASE_TRANSF(PHASE_B, PHASE_B): //B -> B
      *newState = STATE_NOCHANGE;
      break;
    case PHASE_TRANSF(PHASE_B, PHASE_C): //B -> C
      *newState = STATE_FORWARD;
      break;
    case PHASE_TRANSF(PHASE_B, PHASE_D): //B -> D
      *newState = STATE_ERROR;
      break;
    // originating from PHASE_C
    case PHASE_TRANSF(PHASE_C, PHASE_A): //C -> A
      *newState = STATE_ERROR;
      break;
    case PHASE_TRANSF(PHASE_C, PHASE_B): //C -> B
      *newState = STATE_BACKWARDS;
      break;
    case PHASE_TRANSF(PHASE_C, PHASE_C): //C -> C
      *newState = STATE_NOCHANGE;
      break;
    case PHASE_TRANSF(PHASE_C, PHASE_D): //C -> D
      *newState = STATE_FORWARD;
      break;
    // originating from PHASE_D
    case PHASE_TRANSF(PHASE_D, PHASE_A): //D -> A
      *newState = STATE_FORWARD;
      break;
    case PHASE_TRANSF(PHASE_D, PHASE_B): //D -> B
      *newState = STATE_ERROR;
      break;
    case PHASE_TRANSF(PHASE_D, PHASE_C): //D -> C
      *newState = STATE_BACKWARDS;
      break;
    case PHASE_TRANSF(PHASE_D, PHASE_D): //D -> D
      *newState = STATE_NOCHANGE;
      break;
    default: // undefined phase contained in expression
      return -1;  
	}
  return 0;
}

// EOF
