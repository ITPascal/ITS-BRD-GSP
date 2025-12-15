#include "BMP_types.h"
#include "errorhandler.h"
#include "input.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include <stdint.h>
#include "imageProcessor.h"
#define READBUF_MAXSIZE 2400

static char readBuffer[READBUF_MAXSIZE]; 
static uint16_t colors[LCD_WIDTH];

uint16_t lcdColorConversion(RGBQUAD paletteColor, int MODUS) {
    uint16_t red   = paletteColor.rgbRed >> 3;   
    uint16_t green = paletteColor.rgbGreen >> 2; 
    uint16_t blue  = paletteColor.rgbBlue >> 3;
    
    uint16_t color = (red << ((2*5)+1)) | (green << 5) | blue; // 1. 5 bits rot 2. 6 bits gruen 3. 5 bits rot
    return color;
}

static int getEOLPadding(int imageBiWidth) {
    return (4 - (imageBiWidth % 4)) % 4; // padding bei (Bildbreite % 4) != 0
}

static int displayEncMode(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]) {

    uint8_t clrRowEnd = 0;
    uint8_t colorIdx = 0;
    int x = 0;
    
    for (int y = 0; y < displayedHeight; y++) {
        while (x < displayedWidth) {
            clrRowEnd = nextChar() + x;
            colorIdx = nextChar();
            while((x < clrRowEnd) && (x < displayedWidth)) {
                uint16_t lcdClr = lcdColorConversion(palette[colorIdx], 1);
                readBuffer[x] = lcdClr;
                x++;
            }
        }
        uint16_t rowOverlapClr = colorIdx;
        while (x < imageBiWidth) {
            x += nextChar();    // keine while(x < clrRowEnd) {...; x++; ...;} nötig 
            colorIdx = nextChar();
            if (x < imageBiWidth) {
                rowOverlapClr = lcdColorConversion(palette[colorIdx], 1);
            }
        }
        clrRowEnd = x - imageBiWidth;
    }
    return 0;
}

static int displayPointNoEnc(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]) {
    Coordinate screenPos = {0, 0};
    uint16_t color = 0;
    int paletteIdx = 0;

    int unusedPixels = imageBiWidth - displayedWidth; // Pixel außerhalb von Bildbereich
    int eolPadding = getEOLPadding(imageBiWidth);

    for(int y = 0; y < displayedHeight; y++) {

        for (int x = 0; x < displayedWidth; x++) {
            paletteIdx = nextChar();           
            screenPos.x = x;
            screenPos.y = (displayedHeight - 1) - y; 
            color = lcdColorConversion(palette[paletteIdx], 1); //TODO anpassen an MODUS sobald fertig
            GUI_drawPoint(screenPos, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
        }      
        
        for(int i = 0; i < unusedPixels; i++) {
            nextChar();
        }

        for(int j = 0; j < eolPadding; j++) {
            nextChar();
        }
    }
    return 0;
}

static int displayLineNoEnc(int displayedWidth, int displayedHeight, int imageBiWidth, RGBQUAD palette[]) {
    if (imageBiWidth > READBUF_MAXSIZE) {
        ERR_HANDLER(true, "Breite ist zu groß um in Puffer eingelesen zu werden");
        return -1;
    }
    Coordinate lineStart;
    lineStart.x = 0;
    uint16_t clr;

    int eolPadding = getEOLPadding(imageBiWidth);

    for(int y = 0; y < displayedWidth; y++) {
        int rowEntrys = COMread(readBuffer, sizeof(int8_t), imageBiWidth);


        for (int i = 0; i < eolPadding; i++) {
            nextChar(); 
        }

        lineStart.y = y;

        for(int i = 0; i < rowEntrys; i++) {
            clr = lcdColorConversion(palette[(uint8_t) readBuffer[i]], 1); // buf[i] interpretiert als unsigned char // TODO AN MODUS ANPASSEN
            colors[i] = clr;
        }

        GUI_WriteLine(lineStart, rowEntrys, colors);       
    }
    return 0;
}
