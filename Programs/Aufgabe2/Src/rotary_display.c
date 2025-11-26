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
#include "LCD_GUI.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>
#define PRECISION 20

#define ANGLE_TXT "Winkel          :  00,0         Grad"
#define SPEED_TXT "Geschwindigkeit :  0.0          Grad/s"

#define OUT_SYMBOLS 7 
#define OUT_COMMA_IDX 3 
#define TERMN_SPACE 1


#define YPOS_MAX 19
#define YPOS_MIDDLE (19/2)
#define XPOS_ANGLE_TXT 2
#define XPOS_ANGLE_VAL 19
#define XPOS_SPEED_TXT 2
#define XPOS_SPEED_VAL 19

static int charIndex = 0;
static char speedBuffer[(2 * OUT_SYMBOLS) - OUT_COMMA_IDX + TERMN_SPACE]; 
static char angleBuffer[(2 * OUT_SYMBOLS) - OUT_COMMA_IDX + TERMN_SPACE]; 

void initDisplay(void) {
   GUI_init(DEFAULT_BRIGHTNESS);
   lcdGotoXY(XPOS_ANGLE_TXT, YPOS_MIDDLE-2);
   lcdPrintS(ANGLE_TXT);
   lcdGotoXY(XPOS_SPEED_TXT, YPOS_MIDDLE+2);
   lcdPrintS(SPEED_TXT);
}

int CursorToNextChar(void) {
   charIndex = charIndex < (2 * OUT_SYMBOLS) ? charIndex + 1 : 0; // reset after last char was reached
   if(charIndex == OUT_COMMA_IDX || charIndex == (OUT_SYMBOLS + OUT_COMMA_IDX)) {
      charIndex++;
   }
   //TODO: Cursor setzen
   return 0;
}

int updateBuffer(double speed, double angle) {
   char angleS[PRECISION];
   snprintf(angleS, sizeof(angleS), "%f", angle);
   char speedS[PRECISION];
   snprintf(speedS, sizeof(speedS), "%f", speed);
   
   char* angleCmaP = strchr(speedS, '.');
   int   angleCmaIdx = (int) (angleS - angleCmaP);
   char* speedCmaP = strchr(speedS, '.');
   int   speedCmaIdx = (int) (speedS - speedCmaP);

   int trimIdx = speedCmaIdx - OUT_COMMA_IDX;

   memmove((void*) (speedBuffer[0]), (void*) (speedS[trimIdx]), OUT_SYMBOLS - (OUT_COMMA_IDX + TERMN_SPACE));
   //TODO: memmove logik vervollständigen, puffer befüllen und terminator setzten, PRECISION ersetzten
}

int updateChar(void) {
   //TODO: Aktuellen char printen an cursor
}
// EOF
