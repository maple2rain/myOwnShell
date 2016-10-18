#ifndef _TERM_H
#define _TERM_H

#include <stdio.h>
#include <termios.h>

void initTermios(int echo);
void resetTermios(void);

char getch_(int echo);
char getch(void);
char getche(void);

#endif
