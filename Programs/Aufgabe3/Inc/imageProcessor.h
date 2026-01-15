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
#include <stdbool.h>

#define READBUF_MAXSIZE 2400
#define MIN(a,b)   (((a) > (b) ? (a) : (b)))
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
 *  @brief      Diese Funktion ob das Bild per Boxcompression ohne Verzerrung verkleinert
                werden kann. Es werden Verkleinerungen von 1/2, 1/3, 1/4 und 1/5 Unterstützt.
 *
 *  @return     bool isApplicable
 ****************************************************************************************/
bool boxComprApplicable(int imgWidth, int imgHeight);

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
int displayStdEncMode(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]);

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
int displayComprEncMode(BITMAPINFOHEADER infoHeader, RGBQUAD palette[]);
#endif
// EOF