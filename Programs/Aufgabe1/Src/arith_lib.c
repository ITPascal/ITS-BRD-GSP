#include "arith_lib.h"
#include <stdlib.h>
#include <stack.h>
#include <math.h>
#include <display.h>
#include <stdbool.h>

#define NUMTOCHAR 30
/* 
 *  @brief  This auxiliary function returns the arity of value
 *
 *  @param  value   checked value
 *
 *  @return -1 if nullpointer is passed. otherwise 0
 *
*/
int determineArity(int* number) {

    if (number == NULL) {
        return -1;
    }

    int value = *number;
    int arity = 0;

    if(value < 0){
        value = -value;
    }

    for(int i = value; i > 0; i /= 10) {
        arity++;
    }

    *number = arity;

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
    
    stack_pop(&e1);
    stack_pop(&e2);
    
    if (e1 != -1 && e2 != -1) {
        int result = e1+e2;
        stack_push(result);
        return 0;
    } else {
        return -1;
    }

}
int subtraction() {

    int e1 = 0;
    int e2 = 0;
    
    stack_pop(&e1);
    stack_pop(&e2);
    
    if (e1 != -1 && e2 != -1) {
        int result = e2-e1;
        stack_push(result);
        return 0;
    } else {
        return 1;
    }

}

int multiplication() {

    int e1 = 0;
    int e2 = 0;
    
    stack_pop(&e1);
    stack_pop(&e2);
    
    if (e1 != -1 && e2 != -1) {

        int result = e1*e2;

        stack_push(result);

        return 0;
    } else {
        return -1;
    }

}
 int division() {

    int e1 = 0;
    int e2 = 0;
    
    stack_pop(&e1);
    stack_pop(&e2);
    
    if (e1 != -1 && e2 != -1) {

        int result = e2/e1;

        stack_push(result);

        return 0;
    } else {
        return -1;
    }

 }
int printFirst(){
    int value = 0;

    if(stack_pop(&value) != 0){
        return -1;
    }

    stack_push(value);

    char str[12];
    
    //TODO
    

    return 0;
}


    int printAll(){
        //TODO

        return 0;
    }

int clearStack();
int duplicate();
int swapEntries();

