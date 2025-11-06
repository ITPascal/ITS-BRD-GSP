#include "arith_lib.h"
#include <display.h>
#include <Fehlerbehandlung.h>
#include <math.h>
#include <stack.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_INTSTR_LENGTH 16
#define PREFIXLENGTH 1
#define STACK_SIZE 10

/*
 *  @brief  This auxiliary function returns a string representation of value
 *  @param  value   int-Value with arity =< 10
            result  char[size] in which the string is written, size must be > 12
 *  @return
 *
*/
static char *intToString(int value)
{
  static char result[MAX_INTSTR_LENGTH];
  int i = MAX_INTSTR_LENGTH - 1;
  int v = value;

  result[i--] = '\0';
  
  do {
    result[i--] = abs(v % 10) + '0';
    v /= 10;
  } while(v != 0);

  if(value < 0) {
    result[i--] = '-';
  }

  result[i--] = '\n';

  return result + i + 1;
}

int addition(void) {

  int e1 = 0;
  int e2 = 0;

  if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
    return ERR_UNDERFLOW;
  }

  if(e1 > 0 && e2 > 0 && e1 > INT_MAX - e2 || e1 < 0 && e2 < 0 && e1 < INT_MIN - e2 ){
    return ERR_OVERFLOW;
  }

  int result = e1 + e2;

  if (stack_push(result) != 0) {
    return ERR_OVERFLOW;
  }

  return 0;
}

int subtraction(void) {

  int e1 = 0;
  int e2 = 0;

  if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
    return ERR_UNDERFLOW;
  }

  if(e1 > 0 && e2 < 0 && e1 > INT_MAX + e2 || e1 < 0 && e2 > 0 && e1 < INT_MIN + e2 ){
    return ERR_OVERFLOW;
  }

  int result = e2 - e1;

  if (stack_push(result) != 0) {
    return ERR_OVERFLOW;
  }

  return 0;
}

int multiplication(void) {

  int e1 = 0;
  int e2 = 0;

  if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
    return ERR_UNDERFLOW;
  }

  if(e1 > 0 && e2 > 0 && abs(e1) > abs(INT_MAX) / abs(e2) || e1 > 0 && e2 < 0 && abs(e1) > abs(INT_MIN) / abs(e2) 
    || e1 < 0 && e2 > 0 && abs(e1) > abs(INT_MIN) / abs(e2) || e1 < 0 && e2 < 0 && abs(e1) > abs(INT_MAX) / abs(e2) ){

    return ERR_OVERFLOW;

  } 

  int result = e1 * e2;

  if (stack_push(result) != 0) {
    return ERR_OVERFLOW;
  }

  return 0;
}
int division(void) {

  int e1 = 0;
  int e2 = 0;

  if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
    return ERR_UNDERFLOW;
  }

  if(e2 == 0 || e1 == INT_MIN && e2 == -1){
    return ERR_OVERFLOW;
  }

  if (e1 == 0) {
    return ERR_DIVZERO;
  }

  int result = e1 / e2;

  if (stack_push(result) != 0) {
    return ERR_OVERFLOW;
  }


  return 0;
}

int printFirst() {

  int stackValue;
  if (stack_peek(&stackValue) != 0) {
    return ERR_UNDERFLOW;
  }

  printStdout(intToString(stackValue));
  return 0;
}

int printAll(void) {
  for (int i = getStackSize() - 1; i >= 0; i--) {
    printStdout(intToString(stack_get(i)));
  }

  return 0;
}

int duplicate(void) {
  int stackValue;

  if (stack_pop(&stackValue) != 0) {
    return ERR_UNDERFLOW;
  }

  if (stack_push(stackValue) != 0) {
    return ERR_OVERFLOW;
  }

  if (stack_push(stackValue) != 0) {
    return ERR_OVERFLOW;
  }

  return 0;
}

int swapEntries(void) {

  int e1 = 0;
  int e2 = 0;

  if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
    return ERR_UNDERFLOW;
  }

  if (stack_push(e1) != 0 || stack_push(e2) != 0) {
    return ERR_OVERFLOW;
  }

  return 0;
}
