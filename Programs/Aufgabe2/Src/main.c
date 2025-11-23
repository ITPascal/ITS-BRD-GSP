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

#define MASK_LASTPHASE (0x3 << 2)
#define MASK_CURRPHASE 0x3

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
		rotary_determineState((phaseLog & MASK_LASTPHASE), (phaseLog & MASK_CURRPHASE), &state);
		
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
