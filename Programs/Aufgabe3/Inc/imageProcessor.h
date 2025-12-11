/**
  * @file imageProcessor.h
  * @author Julius Sawilski & Pascal Sendecky
  * @date Dec 2025
  * @brief Header datei des imageProcessor Moduls 
  */

#ifndef _IMAGEPROCESSOR_H
#define _IMAGEPROCESSOR_H
#include "BMP_types.h"
#include <stdint.h>

/*
 ****************************************************************************************
 *  @brief      Diese Funktion Codiert ein Pixel codierendes RGBQUAD Struct als 16bit-Wert
 *
 *  @return     uint16_t mit folgender Farbanteilverteilung
 *              bits 0-4:   blau
 *              bits 5-10:  gruen
 *              bits 11-15: rot
 ****************************************************************************************/

uint16_t lcdColorConversion(RGBQUAD paletteColor);
/*
 ****************************************************************************************
 *  @brief      Diese Funktion stellt Pixel für Pixel das eingelesenene Bild dar. Pixel
 *              außerhalb des Bildbereiches werden nicht dargestellt.
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayBitmapImagePoint(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion zeileneweise das eingelesenene Bild dar. Pixel
 *              außerhalb des Bildbereiches werden nicht dargestellt.
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayBitmapImageLine(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);
#endif
// EOF