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
#include "stack.h"
#include "arith_lib.h"

/*
    @brief  Takes a number from the stack and puts the digit on the left

    @param addVal	int containing a positive digit

*/
int postpendNumber(int addVal) {
	if (addVal < 0) {
		return -1;
	}
    int stackVal = 0;
	if (stack_pop(&stackVal) == -1) {
		return -1;
	}

	int result = stackVal * 10 + addVal;
	return 0;
}

int main(void) {

	T_token lastInput;
	lastInput.tok = UNEXPECTED;
	T_token input = {0};

	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();	   // Initialisierung der Taschenrechner GUIs
	TP_Init(false);    // Initialisierung des LCD Boards mit Touch

	while(1) {
		input = nextToken();	//read input
		switch (input.tok) {	//process input
			case NUMBER:
				if (lastInput.tok == NUMBER) {
					postpendNumber(input.val);
				}
				else {
					stack_push(input.val);
				}
				break;
			case PLUS:
				addition();
				break;
			case MINUS: 
				subtraction();
				break;
			case MULT:
				multiplication();
				break;
			case DIV: 
				division();
				break;        
			case PRT:
				printFirst(); 
				break;
			case SWAP:
				swapEntries();
				break;
			case PRT_ALL:
				printAll();
				break;
			case CLEAR:
				clearStack();
				break;
			case DOUBLE:
				duplicate();
				break;
			case ENTER: 
				//nothing
				break;
			case UNEXPECTED:
				break;
			case OVERFLOW:
				break;
			default:
				break;
		}
    lastInput.tok = input.tok;
	lastInput.val = input.val;
	}
}
// EOF
