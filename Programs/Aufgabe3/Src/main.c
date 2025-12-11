/**
  ******************************************************************************
  * @file    main.c
  * @author  Julius Sawilski & Paskal Sendecky (Korrekturen durch AI Partner)
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
#include <math.h> // Für ceil/floor falls nötig
#include <stdlib.h>

#define S7_MASK (1 << 7)
#define PALETTE_SIZE 256
#define FILEHEADER_SIZE 14
#define INFOHEADER_SIZE 40

static RGBQUAD palette[PALETTE_SIZE];


static uint16_t lcdColorConversion(RGBQUAD paletteColor) {
    uint16_t red   = paletteColor.rgbRed >> 3;   
    uint16_t green = paletteColor.rgbGreen >> 2; 
    uint16_t blue  = paletteColor.rgbBlue >> 3;
    
    uint16_t color = (red << ((2*5)+1)) | (green << 5) | blue; // 1. 5 bits rot 2. 6 bits gruen 3. 5 bits rot
    return color;
}

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
            
            COMread((char*)palette, sizeof(RGBQUAD), colorsUsed);
            
            int usedOffBits = FILEHEADER_SIZE + INFOHEADER_SIZE + (PALETTE_SIZE * sizeof(RGBQUAD));
            int paddingOffBits = fileHeader.bfOffBits - usedOffBits;
            int eolPadding = (4 - (infoHeader.biWidth % 4)) % 4;

            for (int i = 0; i < paddingOffBits; i++) { 
                nextChar();
            }

            Coordinate screenPos = {0, 0};
            int paletteIdx = 0;
            uint16_t color = 0;

            for(int y = 0; y < displayedHeight; y++) {
                
                for (int x = 0; x < displayedWidth; x++) {
                    paletteIdx = nextChar();
                    
                    screenPos.x = x;
                    screenPos.y = (displayedHeight - 1) - y; 

                    if (screenPos.x < LCD_WIDTH && screenPos.y < LCD_HEIGHT && screenPos.y >= 0) {
                        color = lcdColorConversion(palette[paletteIdx]);
                        GUI_drawPoint(screenPos, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
                    }
                }
                int unusedPixels = infoHeader.biWidth - displayedWidth;
                for(int k=0; k < unusedPixels; k++) {
                  nextChar();
                }
                for(int p=0; p < eolPadding; p++) {
                    nextChar();
                }
            }
            imageProcessed = true;
        }
        while (nextChar() != EOF){
           //nichts tun
        }
    }
}