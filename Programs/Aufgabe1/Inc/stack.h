#ifndef STACK_H
#define STACK_H

int stack_push(int v);

int stack_pop(int *v);

int stack_peek(int *v);

int stack_get(int pos);

int getStackSize(void);

void resetStack(void);

#endif