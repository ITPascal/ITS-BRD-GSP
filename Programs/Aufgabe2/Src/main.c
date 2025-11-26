/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "init.h"
#include "rotary_calculator.h"
#include "rotary_display.h"
#include "rotary_input.h"
#include "rotary_states.h"
#include "timer.h "
#include <stdint.h>
#include <timer.h>
#include <lcd.h>

#define PHASE_MASK 0x3
#define PHASE_WIDTH 2
#define PHASE_IDX0 (PHASE_MASK << (0 * PHASE_WIDTH))
#define PHASE_IDX1 (PHASE_MASK << (1 * PHASE_WIDTH))
#define MS_PER_TICK (TICKS_PER_US * MS_PER_US)
#define MS_PER_US 1000
#define DEGREE_PER_MOVEMENT ((double) MAX_DEGREES / (double) 360)
#define MAX_DEGREES 1200

int main(void) {
	uint32_t phaseLog = PHASE_A; //no input
	uint32_t in = PHASE_A;
	uint32_t timestamp = 0;
	uint32_t lastUpdate = 0;
	double angle = 0;
	double anglePerSec = 0;
	int state = STATE_NOCHANGE;
	int timeSinceUpdate;
	int movementTracker;
	int phaseCounter;

	initITSboard();
	initDisplay();
	initInput();
	initTimer();

	while(1) {	//TODO: timestamp soll laut aufgabe nach Phasenwechsel erfolgen
		
		//read signal
		while (((timeSinceUpdate >= 250) && (in == (phaseLog & PHASE_IDX0)) || timeSinceUpdate > 500)) {
			timestamp = (double) getTimeStamp() / (double) MS_PER_TICK;
			timeSinceUpdate = (timestamp - lastUpdate);
			readInput(&in);
		}
		phaseLog = phaseLog << PHASE_IDX1;
		phaseLog = phaseLog | in;

		//process signal
		lastUpdate = timestamp;
		rotary_determineState((phaseLog & PHASE_IDX1), (phaseLog & PHASE_IDX0), &state);
			
		//control actuators
		switch (state) {
			case STATE_FORWARD:
				movementTracker = (movementTracker < 360) ? (movementTracker + 1) : 0;
				break;
			case STATE_BACKWARDS:
				movementTracker = (movementTracker > 0) ? (movementTracker - 1) : (360 - 1);
				break;
			case STATE_NOCHANGE:
				//no change
				break;
			case STATE_ERROR:
				return -1;
				break;
			default:
				return -1;
		}
		angle = movementTracker * DEGREE_PER_MOVEMENT;
	}
}

// EOF
