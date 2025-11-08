/**
 ******************************************************************************
 * @file    arith_lib.c
 * @author  Pascal Sendecky, Julius Sawilski
 * @version 1.0
 *
 * @date    07. November 2025
 * @brief   Implementierung der arithmetischen Operationen und Stack-Ausgabe
 *          für den RPN-Taschenrechner.
 *
 *          Beinhaltet Addition, Subtraktion, Multiplikation, Division sowie
 *          Stackoperationen wie Ausgeben, Duplizieren und Tauschen von Elementen.
 *          Fehler wie Overflow, Underflow oder Division durch Null werden korrekt
 *          erkannt und zurückgegeben.
 ******************************************************************************
 */

#include "arith_lib.h"
#include <display.h>
#include <fehlerbehandlung.h>
#include <stack.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_INTSTR_LENGTH 16 /**< Maximale Länge für Integer-Strings */
#define PREFIXLENGTH 1
#define STACK_SIZE 10

/**
 * @brief Wandelt eine Ganzzahl in einen String um.
 * 
 * @param value Ganzzahl, die umgewandelt werden soll
 * @retval char* Zeiger auf den resultierenden String (mit '\n' und '\0' terminiert)
 */
static char *intToString(int value) {
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

/**
 * @brief Addiert die beiden obersten Elemente des Stacks.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn weniger als 2 Elemente im Stack
 * @retval ERR_OVERFLOW   Bei Überlauf
 */
int addition(void) {
    int e1 = 0;
    int e2 = 0;

    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
        return ERR_UNDERFLOW;
    }

    if ((e1 > 0 && e2 > 0 && e1 > INT_MAX - e2) ||
        (e1 < 0 && e2 < 0 && e1 < INT_MIN - e2)) {
        return ERR_OVERFLOW;
    }

    int result = e1 + e2;

    if (stack_push(result) != 0) {
        return ERR_OVERFLOW;
    }

    return 0;
}

/**
 * @brief Subtrahiert das oberste Element vom zweitobersten Element des Stacks.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn weniger als 2 Elemente im Stack
 * @retval ERR_OVERFLOW   Bei Überlauf
 */
int subtraction(void) {
    int e1 = 0;
    int e2 = 0;

    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
        return ERR_UNDERFLOW;
    }

    if ((e1 < 0 && e2 > INT_MAX + e1) || 
        (e1 > 0 && e2 < INT_MIN + e1)) {
        return ERR_OVERFLOW;
    }

    int result = e2 - e1;

    if (stack_push(result) != 0) {
        return ERR_OVERFLOW;
    }

    return 0;
}

/**
 * @brief Multipliziert die beiden obersten Elemente des Stacks.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn weniger als 2 Elemente im Stack
 * @retval ERR_OVERFLOW   Bei Überlauf
 */
int multiplication(void) {
    int e1 = 0;
    int e2 = 0;

    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
        return ERR_UNDERFLOW;
    }

    unsigned int e1_abs = abs(e1);
    unsigned int e2_abs = abs(e2);
    unsigned int min_abs = abs(INT_MIN);

    if ((e1 > 0 && e2 > 0 && e1_abs > INT_MAX / e2_abs) ||
        (e1 > 0 && e2 < 0 && e1_abs > min_abs / e2_abs) ||
        (e1 < 0 && e2 > 0 && e1_abs > min_abs / e2_abs) ||
        (e1 < 0 && e2 < 0 && e1_abs > INT_MAX / e2_abs)) {
        return ERR_OVERFLOW;
    }

    int result = e1 * e2;

    if (stack_push(result) != 0) {
        return ERR_OVERFLOW;
    }

    return 0;
}

/**
 * @brief Dividiert das zweitoberste Element des Stacks durch das oberste Element.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn weniger als 2 Elemente im Stack
 * @retval ERR_DIVZERO    Division durch 0
 * @retval ERR_OVERFLOW   Bei Überlauf
 */
int division(void) {
    int e1 = 0;
    int e2 = 0;

    if (stack_pop(&e1) != 0 || stack_pop(&e2) != 0) {
        return ERR_UNDERFLOW;
    }

    if (e2 == 0 || (e2 == INT_MIN && e1 == -1)) {
        return ERR_OVERFLOW;
    }

    if (e1 == 0) {
        return ERR_DIVZERO;
    }

    int result = e2 / e1;

    if (stack_push(result) != 0) {
        return ERR_OVERFLOW;
    }

    return 0;
}

/**
 * @brief Gibt das oberste Element des Stacks auf dem Display aus.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn der Stack leer ist
 */
int printFirst(void) {
    int stackValue;
    if (stack_peek(&stackValue) != 0) {
        return ERR_UNDERFLOW;
    }

    printStdout(intToString(stackValue));
    return 0;
}

/**
 * @brief Gibt alle Elemente des Stacks auf dem Display aus, vom obersten zum untersten.
 * @retval 0 Erfolgreich
 */
int printAll(void) {
    for (int i = getStackSize() - 1; i >= 0; i--) {
        printStdout(intToString(stack_get(i)));
    }
    return 0;
}

/**
 * @brief Dupliziert das oberste Element des Stacks.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn der Stack leer ist
 * @retval ERR_OVERFLOW   Wenn nicht genügend Platz für Duplikat
 */
int duplicate(void) {
    int stackValue;

    if (stack_pop(&stackValue) != 0) {
        return ERR_UNDERFLOW;
    }

    if (stack_push(stackValue) != 0 || stack_push(stackValue) != 0) {
        return ERR_OVERFLOW;
    }

    return 0;
}

/**
 * @brief Vertauscht die beiden obersten Elemente des Stacks.
 * @retval 0              Erfolgreich
 * @retval ERR_UNDERFLOW  Wenn weniger als 2 Elemente im Stack
 * @retval ERR_OVERFLOW   Wenn Push fehlschlägt
 */
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