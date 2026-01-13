/**
  ******************************************************************************
  * @file    main.c
  * @author  Julius Sawilski & Pascal Sendecky
  ******************************************************************************
  */
#include "BMP_types.h"
#include "errorhandler.h"
#include "headers.h"
#include "stm32f429xx.h"
#include "init.h"
#include "LCD_GUI.h"
#include "input.h"
#include <stdio.h>
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
        GUI_clear(WHITE); 
    }

    if (!imageProcessed) {
        openNextFile();
        imageProcessed = (readHeaders() == NOK); // image processing done if header is NOK
        getFileHeader(&fileHeader);
        getInfoHeader(&infoHeader);
      if (infoHeader.biBitCount != 24) {
        int colorsUsed = (infoHeader.biClrUsed == 0) ? 256 : infoHeader.biClrUsed;    
        COMread((char*)palette, sizeof(RGBQUAD), colorsUsed);
      }
            
      int usedOffBits = FILEHEADER_SIZE + INFOHEADER_SIZE + (PALETTE_SIZE * sizeof(RGBQUAD));
      int paddingOffBits = fileHeader.bfOffBits - usedOffBits;

      for(int i = 0; i < paddingOffBits; i++) { 
        nextChar();
      }
    }

    if (!imageProcessed) {
      // choose display method
      if (infoHeader.biCompression == BI_RLE8) {
        displayEncMode(infoHeader,  palette);
      }
      else if((infoHeader.biCompression == BI_RGB) && infoHeader.biBitCount == 8) {
        displayLineNoEnc(infoHeader, palette);
      }
      else if((infoHeader.biCompression == BI_RGB) && (infoHeader.biBitCount == 24)) {
        displayNoPalette(infoHeader);
      }
      else {
        ERR_HANDLER(true, "Bildformat nicht Unterstuetzt");
      }
      while (nextChar() != EOF) {
        //nothing
      }
      imageProcessed = true;
    }
  }
}