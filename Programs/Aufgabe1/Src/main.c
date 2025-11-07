/**
 ******************************************************************************
 * @file    main.c
 * @author  Pascal Sendecky, Julius Sawilski
 * @version 1.0
 *
 * @date    07. November 2025
 * @brief   Hauptprogramm für einen RPN-Taschenrechner auf dem ITS-Board.
 * 
 *          Dieses Programm liest Eingaben vom Benutzer über die Scanner-Schnittstelle,
 *          verarbeitet die Token und führt arithmetische Operationen auf einem internen
 *          Stack aus. Alle Operationen, die einen Fehler erzeugen (z. B. Overflow, 
 *          Division durch Null, unbekannte Eingaben), werden über die 
 *          Fehlerbehandlungsfunktion handleError() abgefangen.
 *
 *          Unterstützte Operationen:
 *          - Addition, Subtraktion, Multiplikation, Division
 *          - Stack-Operationen: push, pop, swap, duplicate, reset
 *          - Ausgabe einzelner Werte oder aller Stack-Inhalte
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "scanner.h"
#include "init.h"
#include "token.h"
#include <stdbool.h>
#include "stack.h"
#include "arith_lib.h"
#include "fehlerbehandlung.h"

/**
 * @brief Hauptfunktion des RPN-Taschenrechners
 * 
 *        Führt eine Endlosschleife aus, in der Benutzer-Eingaben gelesen,
 *        analysiert und entsprechend verarbeitet werden. Ergebnisse werden
 *        auf dem Display angezeigt und Fehler behandelt.
 * 
 * @retval int Rückgabewert des Programms (immer 0 im Endlosbetrieb)
 */
int main(void) {

    T_token input = {0};
    int result = 0;

    initITSboard();    /**< Initialisierung des ITS-Boards */
    initDisplay();     /**< Initialisierung der Taschenrechner-GUI */

    while(1) {
        input = nextToken(); /**< Liest das nächste Token vom Benutzer */

        switch (input.tok) { /**< Verarbeitung des eingelesenen Tokens */
            case NUMBER:
                result = stack_push(input.val);
                break;
            case PLUS:
                result = addition();
                break;
            case MINUS: 
                result = subtraction();
                break;
            case MULT:
                result = multiplication();
                break;
            case DIV: 
                result = division();
                break;        
            case PRT:
                result = printFirst();
                break;
            case SWAP:
                result = swapEntries();
                break;
            case PRT_ALL:
                printAll();
                break;
            case CLEAR:
                resetStack();
                break;
            case DOUBLE:
                result = duplicate();
                break;
            case ENTER: 
                /**< keine Aktion erforderlich */
                break;
            case UNEXPECTED:
                result = ERR_UNKNOWN;
                break;
            case OVERFLOW:
                result = ERR_OVERFLOW;
                break;
            default:
                break;
        }

        /**< Wenn ein Fehler auftritt, wird er behandelt */
        if(result != 0){
            handleError(result);
        }
    }

    return 0; /**< Endlosprogramm erreicht diese Stelle nie */
}
// EOF