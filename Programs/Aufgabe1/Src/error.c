#include "error.h"
#include "display.h"

void handleError(int v){

    switch (v) {
        setErrMode();
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
