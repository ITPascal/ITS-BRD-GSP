/**
  ******************************************************************************
  * @file    main.c
  * @author  Julius Sawilski & Paskal Sendecky
  * @brief   Main-Klasse die das über USB-UART erhaltene Bilder einließt sie auf
			 dem Display des ITS-Boards ausgibt
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "input.h"


int main(void) {
	initITSboard();
	initInput();
}

// EOF
