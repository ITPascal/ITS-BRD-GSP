/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "display.h"
#include "keypad.h"
#include "scanner.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "token.h"
#include <stdbool.h>
#include <stdlib.h>


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();	   // Initialisierung der Taschenrechner GUIs
	TP_Init(false);    // Initialisierung des LCD Boards mit Touch

	// Test in Endlosschleife
	while(1) {
		printToEchoLine(getKeyPadInput());
	}
}

// EOF
