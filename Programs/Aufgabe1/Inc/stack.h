#ifndef STACK_H
#define STACK_H

int stack_push(int v);

int stack_pop(int *v);
int stack_peek(int *v);
int stack_get(int pos);

int getStackSize(void);

/*
 ****************************************************************************************
 * @brief : This function removes all entries from the stack and sets its size to 0
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/
void resetStack(void);

#endif