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

#define MODE_ABSOLUTE 1
#define MODE_ENCODED 2
#define MODE_RGBPALETTE_LINE 3
#define MODE_RGBNOPALETTE_LINE 4
#define MODE_RGB_POINT 5
/* 
****************************************************************************************
 *  @brief      Diese Funktion ermittelt die Höhe des auf dem Display dargestellten Bildes
 *
 *  @return     int displayedHeight
 ****************************************************************************************/
int getDisplayedHeight(int displayHeight, int imageHeight);

/* 
****************************************************************************************
 *  @brief      Diese Funktion ermittelt die Breite des auf dem Display dargestellten Bildes
 *
 *  @return     int displayedWidth
 ****************************************************************************************/
int getDisplayedWidth(int displayWidth, int imageWidth);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion Codiert ein, einen Pixel codierendes RGBQUAD Struct als 16bit-Wert
 *
 *  @return     uint16_t mit Farbverteilung
 ****************************************************************************************/

uint16_t lcdColorConversion_quad(RGBQUAD color);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion Codiert ein, einen Pixel codierendes RGBTRIPE Struct als 16bit-Wert
 *
 *  @return     uint16_t mit Farbverteilung
 ****************************************************************************************/

uint16_t lcdColorConversion_triple(RGBTRIPLE color);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein unencodiertes 24bit Bild ein
 *
 *  @param      BITMAPINFOHEADER infoheader Enthält informationen zum Bild welches 
 *                                          einzulesen und auszugeben ist
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayNoPalette(BITMAPINFOHEADER infoHeader);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein unendcodiertes Bild ein und gibt es Punkt für Punkt aus
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
                int biHeight        Pixel pro Spalte des gesamten Bildes
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayPointNoEnc(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein unendcodiertes Bild ein und gibt es zeilenweise aus
 *
 *  @param      BITMAPINFOHEADER infoheader Enthält informationen zum Bild welches 
 *                                          einzulesen und auszugeben ist
 *              RGBQUAD palette[]           Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayLineNoEnc(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein encodiertes Bild im Encoded Mode ein und gibt
 *              es zeilenweise aus
 *
 *  @param      BITMAPINFOHEADER infoheader Enthält informationen zum Bild welches 
 *                                          einzulesen und auszugeben ist
 *              RGBQUAD palette[]           Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayEncMode(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]);
#endif
// EOF