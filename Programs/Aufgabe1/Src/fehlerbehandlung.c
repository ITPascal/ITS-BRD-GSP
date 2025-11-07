/**
 ******************************************************************************
 * @file    fehlerbehandlung.c
 * @author  Pascal Sendecky, Julius Sawilski
 * @version 1.0
 *
 * @date    07. November 2025
 * @brief   Implementierung der Fehlerbehandlung für den RPN-Taschenrechner.
 * 
 *          Behandelt verschiedene Fehlercodes (Overflow, Underflow, Division durch Null, 
 *          leerer Stack, unbekannte Fehler) und gibt entsprechende Meldungen über 
 *          das Display aus.
 ******************************************************************************
 */

#include "fehlerbehandlung.h"
#include "display.h"

/**
 * @brief Behandelt einen aufgetretenen Fehler anhand des übergebenen Fehlercodes.
 *        Setzt das Display in den Fehlermodus und gibt eine passende Meldung aus.
 * 
 * @param v Fehlercode, der behandelt werden soll
 *          - ERR_OVERFLOW   : Stacküberlauf
 *          - ERR_UNDERFLOW  : Stackunterlauf
 *          - ERR_DIVZERO    : Division durch Null
 *          - ERR_STACKEMPTY : Stack ist leer
 *          - sonst           : unbekannter Fehler
 * @retval None
 */
void handleError(int v) {

    setErrMode(); /**< Setzt das Display in den Fehlermodus */

    switch (v) {
        case ERR_OVERFLOW:
            printStdout("Fehler: Overflow!");
            break;
        case ERR_UNDERFLOW:
            printStdout("Fehler: Underflow!");
            break;
        case ERR_DIVZERO:
            printStdout("Fehler: Division durch 0!");
            break;
        case ERR_STACKEMPTY:
            printStdout("Fehler: Stack leer!");
            break;
        default:
            printStdout("Unbekannter Fehler!");
            break;
    }
}