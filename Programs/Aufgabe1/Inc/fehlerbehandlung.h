/**
 ******************************************************************************
 * @file    fehlerbehandlung.h
 * @author  Pascal Sendecky,Julius Sawilski
 * @version 1.0
 *
 * @date    07. November 2025
 * @brief   Definition von Fehlercodes und Fehlerbehandlungsfunktionen 
 *          für arithmetische und stackbezogene Operationen.
 ******************************************************************************
 */

#ifndef _FEHLERBEHANDLUNG_H
#define	_FEHLERBEHANDLUNG_H

/**
 * @brief Defaultwert
 * Wird zurückgegeben, wenn alles gut ist.
 */
#define SUCCESS 0

/**
 * @brief Fehlercode: Stacküberlauf
 * Wird zurückgegeben, wenn versucht wird, ein Element auf einen vollen Stack zu legen.
 */
#define ERR_OVERFLOW   -1

/**
 * @brief Fehlercode: Stackunterlauf
 * Wird zurückgegeben, wenn versucht wird, ein Element von einem leeren Stack zu entfernen.
 */
#define ERR_UNDERFLOW  -2

/**
 * @brief Fehlercode: Division durch Null
 * Wird zurückgegeben, wenn eine Division mit Null als Divisor durchgeführt wird.
 */
#define ERR_DIVZERO    -3

/**
 * @brief Fehlercode: Leerer Stack
 * Wird zurückgegeben, wenn eine Operation auf einem leeren Stack durchgeführt werden soll,
 * beispielsweise bei einem Pop-Vorgang.
 */
#define ERR_STACKEMPTY -4

/**
 * @brief Fehlercode: Unbekannter Fehler
 * Wird verwendet, wenn ein unbekannter oder nicht spezifizierter Fehler auftritt.
 */
#define ERR_UNKNOWN    -99

/**
 * @brief Behandelt einen aufgetretenen Fehler anhand des übergebenen Fehlercodes.
 *        Je nach Implementierung kann eine Fehlermeldung ausgegeben oder das Programm 
 *        in einen definierten Zustand zurückgesetzt werden.
 * @param v Fehlercode, der behandelt werden soll
 * @retval None
 */
extern void handleError(int v);

#endif

// EOF