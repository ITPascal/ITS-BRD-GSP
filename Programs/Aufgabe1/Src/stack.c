#include "stack.h"
#include "error.h"

#define STACK_SIZE 10

static int stack[STACK_SIZE];
static int counter = 0;

int stack_push(int v){
    if(counter >= STACK_SIZE){
        return ERR_OVERFLOW;
    }

    stack[counter++] = v;
    
    return 0;
}

int stack_pop(int *v){
    
    if(counter <= 0){
        return ERR_UNDERFLOW;
    }

    *v = stack[--counter];

    return 0;
}

int getStackSize(void){
    return counter;
}

int resetCounter(void) {
    for(int i = 0 ; i < STACK_SIZE; i++){
        stack[i] = 0;
    }
    counter = 0;
}
