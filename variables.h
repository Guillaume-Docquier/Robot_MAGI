#ifndef VARIABLES_H
#define VARIABLES_H

//Pour affichageLCD
#define DEMO_DDR	DDRC // Data Direction Register' AVR occupé par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupé par l'afficheur

//Pour suiveur
#define GAUCHE	0
#define DROITE	1
#define HORS_LIGNE	0
#define SUR_LIGNE	1

//Pour interruptions
#define ANY_EDGE, 1
#define FALLING_EDGE, 2
#define RISING_EDGE, 3
#define LOW_LEVEL, 4

//Variables globales de main.cpp
extern volatile uint8_t ligne;
extern volatile uint8_t coupureligne3;
extern volatile uint8_t ligneADroite9;
extern volatile uint8_t vitesse;
extern volatile uint8_t coupures;

//Variables globales de etape3.cpp
extern volatile bool echoSent; 					
extern volatile bool retrigger;					
extern volatile uint8_t nbFois;					
extern volatile bool direction;					
extern volatile bool fini;						

#endif
