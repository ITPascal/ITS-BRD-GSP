/**
 * @file display.c
 * @author Julius Sawilski & Paskal Sendecky
 * @date Nov 2025
 * @brief This modules implements a simple output,
 *        intendet for displaying an angle and
 *        angle speed for a rotary encoder   
 */

#include "rotary_display.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include <stdio.h>

#define ANGLE_TXT "Winkel          :  0.0          Grad"
#define SPEED_TXT "Geschwindigkeit :  0.0          Grad/s"

#define YPOS_MIDDLE (19 / 2)
#define XPOS_ANGLE_TXT 2
#define XPOS_ANGLE_VAL 19
#define XPOS_SPEED_TXT 2
#define XPOS_SPEED_VAL 19
#define YPOS_ANGLE_TXT (YPOS_MIDDLE - 2)
#define YPOS_SPEED_TXT (YPOS_MIDDLE + 2)
#define BUF_SIZE 10

void initDisplay(void) {
  GUI_init(DEFAULT_BRIGHTNESS);
  lcdGotoXY(XPOS_ANGLE_TXT, YPOS_ANGLE_TXT);
  lcdPrintS(ANGLE_TXT);
  lcdGotoXY(XPOS_SPEED_TXT, YPOS_SPEED_TXT);
  lcdPrintS(SPEED_TXT);
}

char buf_angle[BUF_SIZE], buf_angle_old[BUF_SIZE];
char buf_speed[BUF_SIZE], buf_speed_old[BUF_SIZE];

int idx = 0;

void updateDisplay(double angle, double anglePerSec) {
  if(idx == 0)
  {
    snprintf(buf_angle, BUF_SIZE, "%9.1f", angle);
    snprintf(buf_speed, BUF_SIZE, "%9.1f", anglePerSec);
  }

  if(buf_angle[idx] != buf_angle_old[idx])
  {
    lcdGotoXY(XPOS_ANGLE_VAL + idx, YPOS_ANGLE_TXT);
    lcdPrintC(buf_angle[idx]);
    buf_angle_old[idx] = buf_angle[idx];
  }

  if(buf_speed[idx] != buf_speed_old[idx])
  {
    lcdGotoXY(XPOS_SPEED_VAL + idx, YPOS_SPEED_TXT);
    lcdPrintC(buf_speed[idx]);
    buf_speed_old[idx] = buf_speed[idx];
  }

  ++idx;
  
  if(idx == BUF_SIZE - 1) //last element of buffer
  {
    idx = 0;
  }
}