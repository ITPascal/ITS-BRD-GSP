/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "Fehlerbehandlung.h"
#include "display.h"
#include "scanner.h"
#include "init.h"
#include "LCD_Touch.h"
#include "token.h"
#include <stdbool.h>
#include "stack.h"
#include "arith_lib.h"
#include "fehlerbehandlung.h"

int main(void) {

	T_token input = {0};
	int result = 0;

	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();	   // Initialisierung der Taschenrechner GUIs
	while(1) {
		input = nextToken();	//read input
		switch (input.tok) {	//process input
			case NUMBER:
				result = stack_push(input.val);
				break;
			case PLUS:
				result = addition();
				break;
			case MINUS: 
				result = subtraction();
				break;
			case MULT:
				result = multiplication();
				break;
			case DIV: 
				result = division();
				break;        
			case PRT:
				result = printFirst();
				break;
			case SWAP:
				result = swapEntries();
				break;
			case PRT_ALL:
				printAll();
				break;
			case CLEAR:
				resetStack();
				break;
			case DOUBLE:
				result = duplicate();
				break;
			case ENTER: 
				//nothing
				break;
			case UNEXPECTED:
				result = ERR_UNKNOWN;
				break;
			case OVERFLOW:
				result = ERR_OVERFLOW;
				break;
			default:
				break;
		}

		if(result != 0){
			handleError(result);
		}
	}
}
// EOF
