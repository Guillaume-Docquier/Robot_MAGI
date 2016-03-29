#ifndef PWMMATERIEL_H
#define PWMMATERIEL_H

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

void ajustementPWMPourcentage (uint8_t a, uint8_t b);
//void ajustementPWM (uint8_t operande);
void tournerAdroite(void);
void tournerAGauche(void);
void avancer(uint8_t operande);
void setRotation(uint16_t puissance, bool orientation);
void arreter(void);

#endif
