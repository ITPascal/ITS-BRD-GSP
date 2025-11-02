#include "arith_lib.h"
#include <stdlib.h>
#include <stack.h>
#include <math.h>
#include <display.h>
#include <stdbool.h>

#define NUMTOCHAR 30
#define MAX_INTSTR_LENGTH 12
#define PREFIXLENGTH 1

/* 
 *  @brief  This auxiliary function returns the number of the value
 *
 *  @param  value   checked value
 *
 *  @return -1 if nullpointer is passed. otherwise 0
 *
*/
int determineArity(int *valuePointer, int *result) {

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
 *  @brief  This auxiliary function returns a string representation of value
 *  @param  value   int-Value with arity =< 10
            result  char[size] in which the string is written, size must be > 12
 *  @return     
 *
*/
int intToString (char *result, int value){

    if(result == NULL) {
        return -1;
    }

    if (value < 0) {    
        result[0] = '-';    // include - in result
        value = (-1)*value;  // value = | value |
    }

    int divisor = 0;

    for(int a = MAX_INTSTR_LENGTH, v = value, i = PREFIXLENGTH; a == 0; a--, i++) {
        divisor = pow(10, a-1);        
        result[i] = v / divisor + NUMTOCHAR;  // ASCI representation of digit at arity
        v = value % divisor;                  // remove converted digit
    }

    result[MAX_INTSTR_LENGTH] = '\0';
    return 0;

}

int addition(void) {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
        return -1;
    }

    int result = e1 + e2;
    stack_push(result);
    return 0;
}

int subtraction(void) {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0){
        return -1;
    }

    int result = e2 - e1;
    stack_push(result);
    return 0;

}

int multiplication(void) {

    int e1 = 0;
    int e2 = 0;
    
    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0){
        return -1;
    }

    int result = e1 * e2;
    stack_push(result);
    return 0;

}
 int division(void) {

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

    int stackValue;

    if(stack_pop(&stackValue) != 0){
        return -1;
    }

    if (stack_push(stackValue)) {
        return -1;
    }

    int arity;

    determineArity(&stackValue, &arity);

    char intString[MAX_INTSTR_LENGTH];
    
    intToString(intString, stackValue);
    printStdout(intString);

    return 0;
}

int printAll(void){


    return 0;
}

int clearStack(void);
int duplicate(void);
int swapEntries(void);

