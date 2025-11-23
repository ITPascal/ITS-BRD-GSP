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
#include "rotary_input.h"

int main(void) {
	uint32_t stateSignals = 0;

	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	initInput();
	
	while(1) {
		uint32_t in = 0;

		readInput(&in);
		stateSignals = stateSignals << 2;
		stateSignals = stateSignals | in;

		switch(stateSignals & 0x3) {
			case 0x1:
				lcdPrintS("0x1");
				break;
			case 0x2:
				lcdPrintS("0x2");
				break;
			case 0x3:
				lcdPrintS("0x3");
				break;
			case 0x0:
				lcdPrintS("0x0");
				break;
			default:
				lcdPrintS("non Valid in read");
		}
	}
}

// EOF
