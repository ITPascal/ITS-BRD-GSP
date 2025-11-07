/**
 ******************************************************************************
 * @file    stack.h
 * @author  Pascal Sendecky,Julius Sawilski
 * @version 1.0
 *
 * @date    07. November 2025
 * @brief   Schnittstelle zur Verwaltung eines statischen Stacks für Ganzzahlen.
 *          Beinhaltet Funktionen zum Einfügen, Entfernen und Abfragen von Werten.
 ******************************************************************************
 */

#ifndef STACK_H
#define STACK_H

/**
 * @brief Legt ein Element oben auf den Stack.
 * @param v Wert, der auf den Stack gelegt werden soll
 * @retval 0              Erfolgreich hinzugefügt
 * @retval ERR_OVERFLOW   Stack ist voll
 */
int stack_push(int v);

/**
 * @brief Entfernt das oberste Element vom Stack und gibt es über den Zeiger zurück.
 * @param v Zeiger, über den der entnommene Wert zurückgegeben wird
 * @retval 0              Erfolgreich entfernt
 * @retval ERR_UNDERFLOW  Stack ist leer
 */
int stack_pop(int *v);

/**
 * @brief Liest das oberste Element vom Stack, ohne es zu entfernen.
 * @param v Zeiger, über den der gelesene Wert zurückgegeben wird
 * @retval 0              Erfolgreich gelesen
 * @retval ERR_STACKEMPTY Stack ist leer
 */
int stack_peek(int *v);

/**
 * @brief Gibt den Wert an einer bestimmten Position im Stack zurück,
 *        ohne den Stack zu verändern.
 * @param pos Index im Stack (0 = unterstes Element)
 * @retval Wert an der angegebenen Position
 */
int stack_get(int pos);

/**
 * @brief Liefert die aktuelle Anzahl der Elemente im Stack.
 * @retval Anzahl der Elemente im Stack
 */
int getStackSize(void);

/**
 * @brief Setzt den Stack in seinen Anfangszustand zurück.
 *        Alle gespeicherten Werte werden gelöscht.
 * @retval None
 */
void resetStack(void);

#endif

// EOF