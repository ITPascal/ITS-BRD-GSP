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
 *  @brief      Diese Funktion Codiert ein Pixel codierendes RGBQUAD Struct als 16bit-Wert
 *
 *  @return     uint16_t mit Farbverteilung
 ****************************************************************************************/

uint16_t lcdColorConversion(RGBQUAD paletteColor, int MODE);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein unencodiertes 24bit Bild ein
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
static int displayNoPalette(int displayedHeight, int displayedWidth, int imageBiWidth);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein unendcodiertes Bild ein und gibt es Punkt für Punkt aus
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
static int displayPointNoENc(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein unendcodiertes Bild ein und gibt es zeilenweise aus
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
static int displayLineNoEnc(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein encodiertes Bild im Encoded Mode ein und gibt
 *              es zeilenweise aus
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
static int displayEncMode(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktion ließt ein encodiertes Bild im Absolute Mode ein und gibt
 *              es zeilenweise aus
 *
 *  @param      int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
static int displayAbsMode(int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);

/*
 ****************************************************************************************
 *  @brief      Diese Funktions kapselt die unterschiedliche Implementierungen der zeilenweisen
                Bilddarstellung
 *
 *  @param      int MODUS           jeweillige Konstanten für unterschiedliche Implementierungen einsetzten 
 *              int displayedHeight Höhe des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int displayedWidth  Breite des auf dem Bildschirm darstellbaren Teils des Bilds
 *              int biWidth         Pixel pro Zeile des gesamten Bildes
 *              RGBQUAD palette[]   Zu dazustelldem Bild zugehörige Palette
 *
 *  @returns    int-Wert der Fehler beschreibt
 ****************************************************************************************/
int displayBitmapImage(int MODUS, int displayedHeight, int displayedWidth, int imageBiWidth, RGBQUAD palette[]);
#endif
// EOF