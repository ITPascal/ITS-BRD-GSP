/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "LCD_general.h"
#include "init.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "rotary_calculator.h"
#include "rotary_display.h"
#include "rotary_input.h"
#include "rotary_states.h"

#define PHASE_MASK 0x3
#define PHASE_WIDTH 2
#define PHASE_IDX0 (PHASE_MASK << (0*PHASE_WIDTH))
#define PHASE_IDX1 (PHASE_MASK << (1*PHASE_WIDTH))

int main(void) {
	uint32_t phaseLog = 0;
	uint32_t in = 0;
	int state = STATE_NOCHANGE;

	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();
	initInput();
	int i = 0;

	while(1) {
		//read signal
		readInput(&in);
		phaseLog = phaseLog << (1*PHASE_WIDTH);
		phaseLog = phaseLog | in;

		//process signal
		rotary_determineState((phaseLog & PHASE_IDX1), (phaseLog & PHASE_IDX0), &state);
		
		//control actuators
		switch (state) {
			case STATE_FORWARD:
				break;
			case STATE_BACKWARDS:
				break;
			case STATE_NOCHANGE:
				break;
			case STATE_ERROR:
				break;
			default:
				return -1;
		}
	}
}

// EOF
