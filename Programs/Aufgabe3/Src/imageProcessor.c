#include "BMP_types.h"
#include "errorhandler.h"
#include "input.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include <stdint.h>
#include "imageProcessor.h"
#define READBUF_MAXSIZE 2400
#define EOLN 0x0
#define EOBM 0x1
#define DELTA 0x2

static char readBuffer[READBUF_MAXSIZE]; 
static uint16_t colors[LCD_WIDTH];
int getDisplayedHeight(int displayHeight, int imageHeight) {
    return (imageHeight <= displayHeight) ? imageHeight : displayHeight;
}
int getDisplayedWidth(int displayWidth, int imageWidth) {
    return (imageWidth <= imageWidth) ? imageWidth : displayWidth;
}

uint16_t lcdColorConversion(RGBQUAD paletteColor) {
    uint16_t red   = paletteColor.rgbRed >> 3;   
    uint16_t green = paletteColor.rgbGreen >> 2; 
    uint16_t blue  = paletteColor.rgbBlue >> 3;
    
    uint16_t color = (red << ((2*5)+1)) | (green << 5) | blue; // 1. 5 bits rot 2. 6 bits gruen 3. 5 bits rot
    return color;
}

int getEOLPadding(int imageBiWidth) {
    return (4 - (imageBiWidth % 4)) % 4; // padding bei (Bildbreite % 4) != 0
}

int displayEncMode(BITMAPINFOHEADER info, RGBQUAD palette[]) {
    const int displayedWidth = getDisplayedWidth(LCD_WIDTH, info.biWidth);
    const int displayedHeight = getDisplayedHeight(LCD_HEIGHT, info.biHeight);
    int x = 0;
    int y = 0;
    unsigned char c1 = nextChar();
    unsigned char c2 = nextChar();
    
    if (c1 == 0) {
        switch (c2) {
            case EOLN:
                if (x < displayedWidth) {
                    return ERR_HANDLER(true, "Line nicht komplett gelesen");
                }
                if (y > displayedHeight) {
                    Coordinate lineStart = {0, y};
                    GUI_WriteLine(lineStart, displayedWidth, colors);
                }
                y++;
                x = 0;
                break;
            case EOBM:
                if (y >= displayedHeight) {
                    return 0;
                } 
                else {
                    return ERR_HANDLER(true, "nicht alles auszugebende ausgegeben");
                }
                break;
            case DELTA:
                x = x + nextChar();
                y = y + nextChar();
                break; 
            default: // absolute mode
                if (c2 < 0x02 || c2 > 0xFF) {
                    return ERR_HANDLER(true, 
                        "Anzahl an in Absolute Mode auszugebenden Zeichen ist außerhalb von gültigem Wertebereich");
                }
                int endOfRun = x + c2;
                while (x < endOfRun) {
                    RGBQUAD biColor = palette[nextChar()];
                    uint16_t pxColor = lcdColorConversion(biColor);
                    colors[x] = pxColor;
                    x++;
                }
                if (c2 % 2 != 0) {
                    nextChar();
                }
        }
    }
    else { // b1: count b2: colorIdx 
        uint16_t runColor = lcdColorConversion(palette[c2]);
        int endOfRun = (x + c2) -1;
        while (x <= endOfRun && x < displayedWidth) {
            if (x > info.biWidth) {
                return ERR_HANDLER(true,"x < BitmapBildbreite obwohl das Zeilenende nicht erreicht ist"); 
            }
            colors[x] = runColor;
            x++;
        }
    }
}

int displayPointNoEnc(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]) {
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
            color = lcdColorConversion(palette[paletteIdx]); //TODO anpassen an MODUS sobald fertig
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

int displayLineNoEnc(int displayedWidth, int displayedHeight, int imageBiWidth, RGBQUAD palette[]) {
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
            clr = lcdColorConversion(palette[(uint8_t) readBuffer[i]]); // buf[i] interpretiert als unsigned char // TODO AN MODUS ANPASSEN
            colors[i] = clr;
        }

        GUI_WriteLine(lineStart, rowEntrys, colors);       
    }
    return 0;
}


