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
#include "rotary_states.h"

#define PHASE_TRANSF(p1, p2) ((p1 << ORIG_PHASE_MASK) | (p2 << TRANS_PHASE_MASK))

int rotary_determineState(uint32_t lastPhase, uint32_t currPhase) {

  const int matrix[4][4] =
  {
    { STATE_NOCHANGE,  STATE_FORWARD,   STATE_BACKWARDS, STATE_ERROR     },
    { STATE_BACKWARDS, STATE_NOCHANGE,  STATE_ERROR,     STATE_FORWARD   },
    { STATE_FORWARD,   STATE_ERROR,     STATE_NOCHANGE,  STATE_BACKWARDS },
    { STATE_ERROR,     STATE_BACKWARDS, STATE_FORWARD,   STATE_NOCHANGE  },
  };

  return matrix[lastPhase][currPhase];
}

// EOF
