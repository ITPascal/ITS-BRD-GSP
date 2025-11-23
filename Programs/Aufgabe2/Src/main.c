/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/


#include "init.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "rotary_calculator.h"
#include "rotary_input.h"
#include "rotary_states.h"

int main(void) {
	uint32_t phaseLog = 0;
	uint32_t in = 0;
	int state = STATE_NOCHANGE;

	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	initInput();
	
	while(1) {
		
		//read signal
		readInput(&in);
		phaseLog = phaseLog << 2;
		phaseLog = phaseLog | in;

		//process signal
		rotary_determineState(uint32_t lastPhase, uint32_t currPhase, int *newState)
	}
}

// EOF
