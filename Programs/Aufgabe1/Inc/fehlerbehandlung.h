#ifndef _FEHLERBEHANDLUNG_H
#define	_FEHLERBEHANDLUNG_H

#define ERR_OVERFLOW   -1
#define ERR_UNDERFLOW  -2
#define ERR_DIVZERO    -3
#define ERR_STACKEMPTY -4
#define ERR_UNKNOWN    -99

extern void handleError(int v);

#endif

// EOF