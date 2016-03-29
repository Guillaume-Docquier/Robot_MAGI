#ifndef INTERRUPTIONBOUTON_H
#define INTERRUPTIONBOUTON_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "variables.h"

void initialisationINT0(int edge);
void initialisationTIMER1_COMP(bool A, bool B);
void outputTimer1A(uint16_t duree);
void outputTimer1B(uint16_t duree);


#endif
