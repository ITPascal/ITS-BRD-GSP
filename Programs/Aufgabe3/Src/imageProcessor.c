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

uint16_t lcdColorConversion_quad(RGBQUAD color) {
    uint16_t red   = color.rgbRed >> 3;   
    uint16_t green = color.rgbGreen >> 2; 
    uint16_t blue  = color.rgbBlue >> 3;
    
    uint16_t lcdColor = (red << ((2*5)+1)) | (green << 5) | blue; // 1. 5 bits rot 2. 6 bits gruen 3. 5 bits rot
    return lcdColor;
}

uint16_t lcdColorConversion_triple(RGBTRIPLE color) {
    const uint16_t red   = color.rgbtBlue >> 3;  
    const uint16_t green = color.rgbtGreen >> 2;
    const uint16_t blue  = color.rgbtRed >> 3;
    
    uint16_t lcdColor = (red << ((2*5)+1)) | (green << 5) | blue; // 1. 5 bits rot 2. 6 bits gruen 3. 5 bits rot
    return lcdColor;
}

int getEOLPadding(int imageBiWidth, int bytesPerPixel) {
    return (4 - ((imageBiWidth * bytesPerPixel) % 4)) % 4;
}

int displayEncMode(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]) {
    const int displayedWidth = getDisplayedWidth(LCD_WIDTH, infoHeader.biWidth);
    const int displayedHeight = getDisplayedHeight(LCD_HEIGHT, infoHeader.biHeight);
    int x = 0;
    int y = infoHeader.biHeight -1;
    bool eobmReached = false;

    while (!eobmReached) {
        unsigned char c1 = nextChar();
        unsigned char c2 = nextChar();

        if (c1 == 0) {
            switch (c2) {
                case EOLN:
                    if ((y < displayedHeight) && (y >= 0)) {
                        Coordinate lineStart = {0, y};
                        GUI_WriteLine(lineStart, displayedWidth, colors);
                    }
                    y--;
                    x = 0;
                    break;
                case EOBM:
                    if (y <= 0) {
                        eobmReached = true;
                    } 
                    else {
                        return ERR_HANDLER(true, "nicht alles auszugebende ausgegeben");
                    }
                    break;
                case DELTA:
                    x = x + nextChar();
                    y = y - nextChar();
                    break; 
                default: // absolute mode
                    if (c2 < 0x02 || c2 > 0xFF) {
                        return ERR_HANDLER(true, 
                            "Anzahl an in Absolute Mode auszugebenden Zeichen ist außerhalb von gültigem Wertebereich");
                    }
                    int endOfRun = x + c2;
                    while (x < endOfRun) {
                        RGBQUAD biColor = palette[nextChar()];
                        uint16_t pxColor = lcdColorConversion_quad(biColor);
                        if (x < displayedWidth) {
                        colors[x] = pxColor;
                        }
                        else if (x >= infoHeader.biWidth) {
                            return ERR_HANDLER(true,"x > BitmapBildbreite obwohl das Zeilenende nicht erreicht ist"); 
                        }
                        x++;
                    }
                    if (c2 % 2 != 0) {
                        nextChar();
                    }
            }
        }
        else { // c1: count c2: colorIdx 
            uint16_t runColor = lcdColorConversion_quad(palette[c2]);
            int endOfRun = (x + c1) - 1;
            while (x <= endOfRun) {
                if (x < displayedWidth) {
                    colors[x] = runColor;
                }
                else if (x >= infoHeader.biWidth) {
                    return ERR_HANDLER(true,"x > BitmapBildbreite obwohl das Zeilenende nicht erreicht ist"); 
                }
                x++;
            }
        }
    }
    return 0;
}

int displayPointNoEnc(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]) {
    Coordinate screenPos = {0, 0};
    uint16_t color = 0;
    int paletteIdx = 0;

    int unusedPixels = imageBiWidth - displayedWidth; // Pixel außerhalb von Bildbereich
    int eolPadding = getEOLPadding(imageBiWidth, sizeof(RGBQUAD));

    for(int y = 0; y < displayedHeight; y++) {

        for (int x = 0; x < displayedWidth; x++) {
            paletteIdx = nextChar();           
            screenPos.x = x;
            screenPos.y = (displayedHeight - 1) - y; 
            color = lcdColorConversion_quad(palette[paletteIdx]);
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

int displayLineNoEnc(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]) {
    if (infoHeader.biWidth > READBUF_MAXSIZE) {
        ERR_HANDLER(true, "Breite ist zu groß um in Puffer eingelesen zu werden");
        return -1;
    }

    uint16_t clr;
    const int displayedWidth = getDisplayedWidth(LCD_WIDTH, infoHeader.biWidth);
    const int eolPadding = getEOLPadding(infoHeader.biWidth, sizeof(RGBQUAD));
    const int unusedCharCount = infoHeader.biWidth - (displayedWidth + eolPadding);

    for(int y = 0; y < displayedWidth; y++) {
        Coordinate lineStart = {0, y};
        COMread(readBuffer, sizeof(int8_t), displayedWidth);

        for (int i = 0; i < unusedCharCount; i++) {
            nextChar(); 
        }

        for(int i = 0; i < displayedWidth; i++) {
            RGBQUAD color = palette[readBuffer[i]];
            colors[i] = lcdColorConversion_quad(color);
        }

        GUI_WriteLine(lineStart, displayedWidth, colors);       
    }
    return 0;
}

int displayNoPalette(BITMAPINFOHEADER infoHeader) {
    if (infoHeader.biWidth > READBUF_MAXSIZE) {
        return ERR_HANDLER(true, "Breite ist zu groß um in Puffer eingelesen zu werden");
    }

    const int displayedWidth = getDisplayedWidth(LCD_WIDTH, infoHeader.biWidth);
    const int eolPadding = getEOLPadding(infoHeader.biWidth, sizeof(RGBTRIPLE));

    for (int y = (infoHeader.biHeight -1); y >= 0; y--) {
        
        for (int x = 0; x < infoHeader.biWidth; x++) {
            unsigned char buf[sizeof(RGBTRIPLE)]; 

            COMread(buf, sizeof(unsigned char), sizeof(RGBTRIPLE));
            if (x < displayedWidth) {
                RGBTRIPLE* color = (RGBTRIPLE*) buf;
                colors[x] = lcdColorConversion_triple(*color);
            }
        }
        for (int i = 0; i < eolPadding; i++) {
            nextChar(); //nichts tun
        }
        Coordinate lineStart = {0, y};
        GUI_WriteLine(lineStart, displayedWidth, colors);
    }
    return 0;
}

