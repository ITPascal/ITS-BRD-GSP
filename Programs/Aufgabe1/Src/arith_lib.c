#include "arith_lib.h"
#include <stdlib.h>
#include <stack.h>
#include <math.h>
#include <display.h>
#include <stdbool.h>

#define NUMTOCHAR 30
#define PREFIXSLOT 1
/* 
 *  @brief  This auxiliary function returns the arity of value
 *
 *  @param  value   checked value
 *
 *  @return -1 if nullpointer is passed. otherwise 0
 *
*/
int determineArity(int* valuePointer, int* result) {

    if (valuePointer == NULL) {
        return -1;
    }

    int value = *valuePointer;
    int arity = 0;

    if(value < 0){
        value = -value;
    }

    for(int i = value; i > 0; i /= 10) {
        arity++;
    }

    *result = arity;

    return 0;
}

/* 
 *  @brief  This auxiliary function returns a string representation of a number
 *  @param  value positive integer to be converted 
            result  container for writing the string, minimum size:
                    if value is positive result[arity]
                    if value is negative result[arity+1]
 *  @return     
 *
*/
int intToString (char *result, int value, int arity){

    if(result == NULL) {
        return -1;
    }

    if (value < 0) {    
        result[0] = '-';    // include - in result
        value = (-1)*value;  // value = | value |
    }

    int divisor = 0;

    for(int a = arity, v = value, i = value < 0 ? 1 : 0; i > 0; a--, i++) {

        divisor = pow(10, a-1);

        result[i] = (v / divisor) + NUMTOCHAR;  // ASCI representation of digit at arity

        v = value % divisor;                    // remove converted digit
    }

    return 0;

}

int addition() {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
        return -1;
    }

    int result = e1 + e2;
    stack_push(result);
    return 0;
}

int subtraction() {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0){
        return -1;
    }

    int result = e2 - e1;
    stack_push(result);
    return 0;

}

int multiplication() {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0){
        return -1;
    }

    int result = e1 * e2;
    stack_push(result);
    return 0;

}
 int division() {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0){
        return -1;
    }

    int result = e1 / e2;
    stack_push(result);
    return 0;
 }

int printFirst(){
    int stackValue = 0;

    if(stack_pop(&stackValue) != 0){
        return -1;
    }

    if (stack_push(stackValue)) {
        return -1;
    }

    int arity;

    determineArity(&stackValue, &arity);

    int length = (stackValue > 0) ? arity : (PREFIXSLOT + arity);
    char intString[length];
    
    intToString(intString, stackValue, arity);
    printStdout(intString);

    return 0;
}

int printAll(){


    return 0;
}

int clearStack();
int duplicate();
int swapEntries();

