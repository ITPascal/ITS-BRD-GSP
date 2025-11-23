/**
  * @file display.c
  * @author Franz Korf, HAW Hamburg 
  * @date Mar 2016
  * @brief This modules implements a simple output module. 
  *        It places two terminals in the terminal area of keypad.
  *        One terminal will be used for standard output. The other one
  *        echos pressed digit keys.
  */

#include "rotary_display.h"
#include <stdlib.h>
#include "LCD_GUI.h"
#include "lcd.h"

#define ANGLE_TXT "Winkel          :  00,0         Grad"
#define SPEED_TXT "Geschwindigkeit :  0.0          Grad/s"

#define ANGLE_SYMBOLS 4
#define ANGLE_COMMA_IDX 2
#define SPEED_SYMBOLS 3
#define SPEED_COMMA_INX 1

#define YPOS_MAX 19
#define YPOS_MIDDLE (19/2)
#define XPOS_ANGLE_TXT 2
#define XPOS_ANGLE_VAL 19
#define XPOS_SPEED_TXT 2
#define XPOS_SPEED_VAL 19

int charIndex = 0;

void initDisplay(void) {
   GUI_init(DEFAULT_BRIGHTNESS);
   lcdGotoXY(XPOS_ANGLE_TXT, YPOS_MIDDLE-2);
   lcdPrintS(ANGLE_TXT);
   lcdGotoXY(XPOS_SPEED_TXT, YPOS_MIDDLE+2);
   lcdPrintS(SPEED_TXT);
}

int gotoNextChar(void) {
   charIndex = charIndex < (ANGLE_SYMBOLS + SPEED_SYMBOLS) ? charIndex + 1 : 0;
   if(charIndex == ANGLE_COMMA_IDX || charIndex == (ANGLE_SYMBOLS + SPEED_COMMA_INX)) {
      charIndex++;
   }
}

int updateChar(double speed, double angle) {
}
// EOF
