#include "stack.h"
#include "Fehlerbehandlung.h"

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

int stack_peek(int *v)
{
    if(counter <= 0){
        return ERR_UNDERFLOW;
    }

    *v = stack[counter - 1];
    return 0;
}

int stack_get(int pos)
{
    return stack[pos];
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

void resetStack(){
    counter = 0;
    for(int i = 0 ; i < STACK_SIZE; i++){
        stack[i] = 0;
    }
}
