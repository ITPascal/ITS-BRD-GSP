#include "arith_lib.h"
#include <display.h>
#include <scanner.h>
#include <token.h>
#include <stack.h>
#include <keypad.h>

T_token lastInput = {0}; // enthält den letzten Input


/*
    @brief  Fügt addVal links an die erste int auf dem Stack an

    @param addVal   einstelliger positiver int-Wert

*/
int prependNumber(int addVal) {
    int stackVal = 0;

    if(stack_pop(&stackVal) != -1){

        int result = stackVal * 10 + addVal;

    }
}

/*
    @brief Ruft je nach Tokentyp und altem token passende Operation aus


*/

int processInput(T_token input) {
    switch (input.tok) {
        case NUMBER:
            if (lastInput.tok == NUMBER) {
                prependNumber(input.val);
            }
            else {
                stack_push(input.val);
            }
            break;
        case PLUS:
            addition();
            break;
        case MINUS: 
            subtraction();
            break;
        case MULT:
            multiplication();
            break;
        case DIV: 
            division();
            break;        
        case PRT:
            printFirst(); 
            break;
        case SWAP:
            break;
        case PRT_ALL:
            break;
        case CLEAR:
            break;
        case DOUBLE:
            break;
        case ENTER:
            break;
        case UNEXPECTED:
            break;
        case OVERFLOW:
            break;
        default:
            break;
    }
    lastInput = input;
    return 0;
}