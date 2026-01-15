#include "BMP_types.h"
#include "errorhandler.h"
#include "input.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "imageProcessor.h"
#define MAX_BOXSIZE 5
#define READBUF_MAXSIZE (LCD_WIDTH * (MAX_BOXSIZE * MAX_BOXSIZE))
#define MIN(a,b)   (((a) > (b) ? (a) : (b)))
#define EOLN 0x0
#define EOBM 0x1
#define DELTA 0x2

static char readBuffer[READBUF_MAXSIZE]; 
static uint16_t colors[LCD_WIDTH];

int getDisplayedHeight(int displayHeight, int imageHeight) {
    return (imageHeight <= displayHeight) ? imageHeight : displayHeight;
}

int getDisplayedWidth(int displayWidth, int imageWidth) {
    return (imageWidth <= displayWidth) ? imageWidth : displayWidth;
}

bool boxComprApplicable(int imgWidth, int imgHeight) {
    double scale_x = LCD_WIDTH / ((double) imgWidth);
    double scale_y = LCD_HEIGHT / ((double) imgHeight);
    double scale = MIN(scale_x, scale_y);
    for (int i = 1; i <= 5; i++) {
        if (((double) 1 / i) == scale) {
            return (scale < 1);
        }
    }
    return false;
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
static int getAvgBoxPx(unsigned char *box[], int box_width, int box_height, RGBQUAD* palette, int paletteSize) {
    uint32_t blueSum = 0;
    uint32_t greenSum = 0;
    uint32_t redSum = 0;
    
    for(int y = 0; y < box_height; y++) {
        for (int x = 0; x < box_width; x++) {
            unsigned char *currRow = box[y];
            if (currRow[x] > paletteSize) {
                ERR_HANDLER(true, "FarbIndex außerhalb des gültigen Wertebereichs");
            }
            RGBQUAD *color_struct = &palette[currRow[x]];
            blueSum += color_struct->rgbBlue;
            greenSum += color_struct->rgbGreen;
            redSum += color_struct->rgbRed;
        }
    }
    blueSum /= (box_height * box_width);
    greenSum /= (box_height * box_width);
    redSum /= (box_height * box_width);
    RGBQUAD avrColor = {
        (uint16_t) blueSum,
        (int16_t) greenSum,
        (uint16_t) redSum 
    };
    return lcdColorConversion_quad(avrColor);
}

int displayComprEncMode(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]) {
    const double scale_x = LCD_WIDTH / ((double) infoHeader.biWidth);
    const double scale_y = LCD_HEIGHT / ((double) infoHeader.biHeight);
    const double scale = MIN(scale_x, scale_y);

    const int normBox_width = (int) ceil(1 / scale);
    const int normBox_height = (int) ceil(1 / scale);

    int displayedWidth  = (int)floor((infoHeader.biWidth * scale) + 0.5);
    int displayedHeight = (int)floor((infoHeader.biHeight * scale) + 0.5);
    displayedHeight = (displayedHeight <= LCD_HEIGHT) ? displayedHeight : LCD_HEIGHT;
    displayedWidth = (displayedWidth <= LCD_WIDTH) ? displayedWidth : LCD_WIDTH;
    const int paletteSize = (infoHeader.biClrUsed == NULL) ? 256 : infoHeader.biClrUsed; 

    bool eobmReached = false;

    int out_x = 0;
    int out_y = displayedHeight - 1;
    int in_y = infoHeader.biHeight -1;
    int in_x = 0;

    int rowsRead = 0;
    while (!eobmReached) {
        int box_width = normBox_width;
        int box_height = normBox_height;
        if ((in_x + normBox_width) >= infoHeader.biWidth) {
            box_width = ((infoHeader.biWidth - 1) - in_x);
        }
        if ((in_y - normBox_height) < 0) {
            box_height = in_y + 1;
        }
        // read input
        while(!eobmReached && (rowsRead < box_height)) {
            unsigned char c1 = nextChar();
            unsigned char c2 = nextChar();
            int endOfRun = 0;
        
            if (c1 == 0) {
                switch (c2) {
                    case EOLN:
                        in_y--;
                        in_x = 0;
                        rowsRead++;
                        break;
                    case EOBM:
                        eobmReached = true;
                        in_x = 0;
                        in_y--;
                        break;
                    case DELTA:
                        in_x = in_x + nextChar();
                        in_y = in_y - nextChar();
                    default: // absolute mode
                        if (c2 < 0x02 || c2 > 0xFF) {
                            return ERR_HANDLER(true, 
                            "Anzahl an in Absolute Mode auszugebenden Zeichen ist außerhalb von gültigem Wertebereich");
                        }   
                        endOfRun = in_x + c2;
                        while (in_x < endOfRun) {
                            if (in_x >= infoHeader.biWidth || in_x < 0) {
                                return ERR_HANDLER(true, "Absolute Mode: x-Koordinate ist ausserhalb von Bildbereich"); 
                            }
                            readBuffer[in_x + (rowsRead * infoHeader.biWidth)] = nextChar();
                            in_x++;
                        }
                        if (c2 % 2 != 0) {
                            nextChar();
                        }   
                        break;
                }
            }
            else { // c1: count c2: colorIdx 
                endOfRun = in_x + c1;
                while (in_x < endOfRun) {
                    if ((in_x >= infoHeader.biWidth) || (in_x < 0)) {
                        return ERR_HANDLER(true,"RLE-Codierungx: x-Koordinate von Pixel ist ausserhalb vom Bildbereich"); 
                    }
                    readBuffer[in_x + (rowsRead * infoHeader.biWidth)] = c2;
                    in_x++;
                }
            }
        }
        // write output
        if (out_y >= 0) {
            while (out_x < displayedWidth) {
                unsigned char* box[box_height];
                for(int i = 0; i < box_height; i++) {
                    int currBox_rowStart = (i * infoHeader.biWidth);
                    int currBox_x = (int) floor(out_x/scale_x);
                    unsigned char* boxRow = (unsigned char*) &readBuffer[currBox_rowStart + currBox_x];
                    box[i] = boxRow;
                }
                colors[out_x] = (uint16_t) getAvgBoxPx(box, box_width, box_height, palette, paletteSize);
                out_x++;
            }
            //display output
            Coordinate out_lineStart = {0, out_y};
            GUI_WriteLine(out_lineStart, displayedWidth, colors);
        }
        out_y--;
        out_x = 0;
        rowsRead = 0;
    }
    return 0;
}


int displayStdEncMode(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]) {
    const int displayedWidth = getDisplayedWidth(LCD_WIDTH, infoHeader.biWidth);
    const int displayedHeight = getDisplayedHeight(LCD_HEIGHT, infoHeader.biHeight);
    int x = 0;
    int y = infoHeader.biHeight -1;
    bool eobmReached = false;

    while (!eobmReached) {
        unsigned char c1 = nextChar();
        unsigned char c2 = nextChar();

        if ((y >= infoHeader.biHeight) || (y < -1)) {
            return ERR_HANDLER(true,"ungueltiger y-Wert"); 
        }

        if (c1 == 0) {
            switch (c2) {
                case EOLN:
                    if (y < displayedHeight) {
                        Coordinate lineStart = {0, y};
                        GUI_WriteLine(lineStart, displayedWidth, colors);
                    }
                    y--;
                    x = 0;
                    break;
                case EOBM:
                    if (x > 0 && y < displayedHeight && y >= 0) {
                        Coordinate lineStart = {0, y};
                        GUI_WriteLine(lineStart, displayedWidth, colors);
                        y--;
                    }
                    eobmReached = true;
                    if (y > -1) {
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
                    break;
            }
        }
        else { // c1: count c2: colorIdx 
            uint16_t runColor = lcdColorConversion_quad(palette[c2]);
            int endOfRun = (x + c1) - 1;
            while (x <= endOfRun) {
                if ((x < displayedWidth) && (y < displayedHeight)) {
                    colors[x] = runColor;
                }
                else if ((x > infoHeader.biWidth) || (x < 0)) {
                    return ERR_HANDLER(true,"x-Koordinate von Pixel ist ausserhalb von in Infoheader angegebenem Bildbereich"); 
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
    uint16_t color;
    const int eolPadding = getEOLPadding(infoHeader.biWidth, sizeof(RGBQUAD));
    const double scale_x = LCD_WIDTH / ((double) infoHeader.biWidth);
    const double scale_y = LCD_HEIGHT / ((double) infoHeader.biHeight);
    const double scale = MIN(scale_x, scale_y);
    const int normBox_width = (int) ceil(1 / scale);
    const int normBox_height = (int) ceil(1 / scale);
    const int displayedWidth  = (int)floor((infoHeader.biWidth * scale) + 0.5); // varies from other display methods
    const int displayedHeight = (int)floor((infoHeader.biHeight * scale) + 0.5); // -"-

    
    for(int img_y = (displayedHeight - 1); img_y >= 0; img_y--) {
        for(int i = 0; i < normBox_height; i++) {   // TODO: Nicht zwingend immer normbox Hight, immer größeren Wert nehemn
                COMread(&readBuffer[i * infoHeader.biWidth], sizeof(char),infoHeader.biWidth);
                for(int j = 0; j < eolPadding; j++) {
                    nextChar(); // nichts tun
                }
            }
            
        for (int img_x = 0; img_x < displayedWidth; img_x++) {
            
            int box_x = floor(img_x/scale_x);
            int box_y = floor(img_y/scale_y);

            int box_width = normBox_width;
            int box_height = normBox_height;

            if ((box_x + normBox_width) >= infoHeader.biWidth) {
                box_width = (infoHeader.biWidth - box_x);
            }
            
            if ((box_y + normBox_height) > infoHeader.biHeight) {
                box_height = (infoHeader.biHeight - box_y);
            }
            
            unsigned char* BoxArr[box_height]; // pointers to box_x with offset for different rows
            for (int i = 0; i < box_height; i++) {  
                int boxRowIdx = i * infoHeader.biWidth;
                BoxArr[i] = (unsigned char*) &readBuffer[boxRowIdx + box_x];
            }
            int paletteSize = infoHeader.biClrUsed == NULL ? 256 : infoHeader.biClrUsed;
            colors[img_x] = getAvgBoxPx((unsigned char**) BoxArr, box_width, box_height, palette, paletteSize);
        }
        Coordinate lineStart = {0, img_y};
        GUI_WriteLine(lineStart, LCD_WIDTH, colors);
    }
    return 0;
}

int displayNoPalette(BITMAPINFOHEADER infoHeader) {
    if (infoHeader.biWidth > READBUF_MAXSIZE) {
        return ERR_HANDLER(true, "Breite ist zu groß um in Puffer eingelesen zu werden");
    }

    const int displayedWidth = getDisplayedWidth(LCD_WIDTH, infoHeader.biWidth);
    const int displayedHeight = getDisplayedHeight(LCD_HEIGHT, infoHeader.biHeight);
    const int eolPadding = getEOLPadding(infoHeader.biWidth, sizeof(RGBTRIPLE));
    const int unusedTripleCount = infoHeader.biWidth - (displayedWidth + eolPadding);

    for (int y = (infoHeader.biHeight -1); y >= 0; y--) {
        
        COMread((char*)readBuffer, sizeof(RGBTRIPLE), displayedWidth);
        
        if (y < displayedHeight) {
            RGBTRIPLE* readBufferP = (RGBTRIPLE*) &readBuffer;
            for (int x = 0; x < displayedWidth; x++) {
                uint16_t color = lcdColorConversion_triple(readBufferP[x]);
                colors[x] = color;
            }
            Coordinate lineStart = {0, y};
            GUI_WriteLine(lineStart, displayedWidth, colors);
        }
        COMread(readBuffer, sizeof(RGBTRIPLE), unusedTripleCount); //read unused chars
    }
    return 0;
}