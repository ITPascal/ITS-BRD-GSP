/**
  ******************************************************************************
  * @file    main.c
  * @author  Julius Sawilski & Paskal Sendecky
  * @brief   Main-Klasse die das über USB-UART erhaltene Bilder einließt sie auf
			 dem Display des ITS-Boards ausgibt
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "BMP_types.h"
#include "headers.h"
#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "input.h"
#include "MS_basetypes.h"
#include "errorhandler.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include <stdio.h>

#define S7_MASK (1 << 7)
#define PALETTE_SIZE 256

static RGBQUAD palette[PALETTE_SIZE];

int main(void) {
	initITSboard();
	initInput();

  BITMAPFILEHEADER file = {0,0,0,0,0};
  BITMAPINFOHEADER info = {0,0,0,0,0,0,0,0,0,0,0};
  Coordinate cords = {0,0};
  bool buttonPressed = true;

  while(1) {
    buttonPressed = (GPIOF->IDR & S7_MASK); //knopfdruck auf S7 lesen
    if (buttonPressed) {
      openNextFile(); //Todo: Erste File öffnen ohne Knopfdruck, dannach erst prüfen
    }
    if (readHeaders() != -1) {  // header lesen
        getFileHeader(&file);
        getInfoHeader(&info);
    }
    
    COMread((char*)palette, sizeof(RGBQUAD), PALETTE_SIZE); //palette lesen und speichern
    int bitmapPaletteOffset = file.bfOffBits - (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (info.biClrUsed * sizeof(RGBQUAD)));

    for (int i = 0; i < bitmapPaletteOffset; i++) { // lesen bis an bitmap
      nextChar();
    }
  
    int colorP = 0;

    while((colorP = nextChar()) != EOF) {
      //TODO: Punkte zeichnen
    }
  }
}

// EOF
