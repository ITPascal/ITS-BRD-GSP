#include "stack.h"

#define STACK_SIZE 10

static int stack[STACK_SIZE];
static int counter = 0;

int stack_push(int v){
    if(counter >= STACK_SIZE){
        return -1;
    }

    stack[counter++] = v;
    
    return 0;
}

int stack_pop(int *v){
    
    if(counter <= 0){
        return -1;
    }

    *v = stack[--counter];

    return 0;
}

int getStackSize(){
    return counter;
}