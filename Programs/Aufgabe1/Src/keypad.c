#include <display.h>
#include <scanner.h>
#include <token.h>
#include <stack.h>

int prependNumber(int addVal);

T_token lastInput = {0}; // enthält den letzten Input

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
            
            break;
        case MINUS: 
            break;
        case MULT: 
            break;
        case DIV: 
            break;        
        case PRT: 
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
/*
    @brief  Fügt addVal links an die erste int auf dem Stack an

    @param addVal   einstelliger positiver int-Wert

*/
int prependNumber(int addVal) {
    int reqArity = 0;
    int stackVal = 0;
    if (stack_pop(&stackVal) != -1) {
        reqArity = 1;
        for(int i = stackVal; i>0;i/=10) {
            reqArity++;
        }
        int result = stackVal+(reqArity*addVal);
        stack_push(result);
    }
    else {
        return -1;
    }
    return 0;
}