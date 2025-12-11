/**
  ******************************************************************************
  * @file    main.c
  * @author  Julius Sawilski & Paskal Sendecky
  ******************************************************************************
  */
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
#include "LCD_general.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "imageProcessor.h"

#define S7_MASK (1 << 7)
#define PALETTE_SIZE 256
#define FILEHEADER_SIZE 14
#define INFOHEADER_SIZE 40
#define BIWIDTH_TOOLARGE 1500

static RGBQUAD palette[PALETTE_SIZE];

int main(void) {
    initITSboard();
    initInput();
    GUI_init(DEFAULT_BRIGHTNESS);

    BITMAPFILEHEADER fileHeader = {};
    BITMAPINFOHEADER infoHeader = {};
    int currentButtonState = 0;
    bool imageProcessed = false;
    bool buttonPressed = false;

    while(1) {
        currentButtonState = (GPIOF->IDR & S7_MASK);
        if (currentButtonState == 0) {
          imageProcessed = false;
        }

        if (!imageProcessed) {
            GUI_clear(WHITE);
            openNextFile();
            readHeaders();
            getFileHeader(&fileHeader);
            getInfoHeader(&infoHeader);

            int displayedHeight = (infoHeader.biHeight <= LCD_HEIGHT) ? infoHeader.biHeight : LCD_HEIGHT;
            int displayedWidth = (infoHeader.biWidth <= LCD_WIDTH) ? infoHeader.biWidth : LCD_WIDTH;
            int colorsUsed = (infoHeader.biClrUsed == 0) ? 256 : infoHeader.biClrUsed;    
            
            COMread((char*)palette, sizeof(RGBQUAD), colorsUsed); // TODO vorher auf Unterschiedliche Codierungen prüfen
            
            int usedOffBits = FILEHEADER_SIZE + INFOHEADER_SIZE + (PALETTE_SIZE * sizeof(RGBQUAD));
            int paddingOffBits = fileHeader.bfOffBits - usedOffBits;

            for (int i = 0; i < paddingOffBits; i++) { 
                nextChar();
            }
            
            if (displayBitmapImage(1, displayedHeight, displayedWidth, infoHeader.biWidth, palette) != 0) { //TODO Anpassen wenn imageProcessor fertig
              ERR_HANDLER(true, "Fehler während ausgeben von Bild");
            }

            while (nextChar() != EOF){
              //nichts tun
            }
            imageProcessed = true;
        }
    }
}