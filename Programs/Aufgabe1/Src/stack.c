/**
 ******************************************************************************
 * @file    stack.c
 * @author  Pascal Sendecky
 * @version 1.0
 *
 * @date    07. November 2025
 * @brief   Implementierung eines einfachen statischen Stacks für Ganzzahlen.
 *          Beinhaltet Funktionen zum Einfügen, Entfernen, Abfragen und Zurücksetzen
 *          von Werten. Fehler wie Overflow oder Underflow werden über Fehlercodes
 *          zurückgegeben.
 ******************************************************************************
 */

#include "stack.h"
#include "fehlerbehandlung.h"

#define STACK_SIZE 10 /**< Maximale Größe des Stacks */

static int stack[STACK_SIZE]; /**< Speicher für Stack-Elemente */
static int counter = 0;       /**< Aktuelle Anzahl der Elemente im Stack */

/**
 * @brief Legt ein Element oben auf den Stack.
 * @param v Wert, der auf den Stack gelegt werden soll
 * @retval 0              Erfolgreich hinzugefügt
 * @retval ERR_OVERFLOW   Stack ist voll
 */
int stack_push(int v) {
    if(counter >= STACK_SIZE) {
        return ERR_OVERFLOW;
    }
    stack[counter++] = v;
    return 0;
}

/**
 * @brief Liest das oberste Element vom Stack, ohne es zu entfernen.
 * @param v Zeiger, über den der Wert zurückgegeben wird
 * @retval 0              Erfolgreich gelesen
 * @retval ERR_UNDERFLOW  Stack ist leer
 */
int stack_peek(int *v) {
    if(counter <= 0) {
        return ERR_UNDERFLOW;
    }
    *v = stack[counter - 1];
    return 0;
}

/**
 * @brief Gibt den Wert an einer bestimmten Position im Stack zurück,
 *        ohne den Stack zu verändern.
 * @param pos Index im Stack (0 = unterstes Element)
 * @retval Wert an der angegebenen Position
 */
int stack_get(int pos) {
    return stack[pos];
}

/**
 * @brief Entfernt das oberste Element vom Stack und gibt es über den Zeiger zurück.
 * @param v Zeiger, über den der entnommene Wert zurückgegeben wird
 * @retval 0              Erfolgreich entfernt
 * @retval ERR_UNDERFLOW  Stack ist leer
 */
int stack_pop(int *v) {
    if(counter <= 0) {
        return ERR_UNDERFLOW;
    }
    *v = stack[--counter];
    return 0;
}

/**
 * @brief Liefert die aktuelle Anzahl der Elemente im Stack.
 * @retval Anzahl der Elemente im Stack
 */
int getStackSize(void) {
    return counter;
}

/**
 * @brief Setzt den Stack in seinen Anfangszustand zurück.
 *        Alle gespeicherten Werte werden gelöscht.
 * @retval None
 */
void resetStack() {
    counter = 0;
    for(int i = 0; i < STACK_SIZE; i++) {
        stack[i] = 0;
    }
}