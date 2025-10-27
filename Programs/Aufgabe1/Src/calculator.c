#include "calculator.h"
#include <stack.h>
#include <math.h>
#include <display.h>

#define NUMTOCHAR 30
/* 
 *  @brief   Hilfsfuntkion die den übergebenen int-Wert in einen String umwandelt
 *  @param  positive Ganzzahl, die umgewandelt werden soll
 *  @return giebt einen Pointer der auf den umgewandlungsstring zeigt zurück
 *
*/
char* intToString (int value, char* result){
    int arity = 0; 
    for(int i = value; i>0;i/=10) { // Prüft welche Stelligkeit die Zahl hat
        arity++;
    }
    char numString[arity];  // String der Zahl abbildet 
    int arityDivisor = 0;   
    for (int i = arity, j = value, n=0; i > 0; i--,n++) { // stelligkeit i sinkt, arrayindex n steigt
        arityDivisor = pow(10, i-1); // 10er potenz ermitteln
        numString[i + NUMTOCHAR] =  j/arityDivisor; // Zifferchar an stelle i in array an stelle n schreiben
        j = value%arityDivisor; // geschriebene Ziffer aus j entfernen
    }
    result = numString;
    return result; //Prüfen: Wie mit groesse der übergebenen Variable result umgehen?
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
    }
    else {
        return 1;
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
    }
    else {
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
    }
    else {
        return 1;
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
    }
    else {
        return 1;
    }
 }
int printFirst();
int printAll();
int clearStack();
int duplicate();
int swapEntries();

