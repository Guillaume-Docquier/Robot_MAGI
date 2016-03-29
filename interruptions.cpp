#include "interruptions.h"

void initialisationINT0(int edge){
	cli();

	//Reset register (Default = low level)
	EICRA &= ~(1<<ISC00) & ~(1<<ISC10);						

	//Set interruption options
	if(edge == ANY_EDGE)
		EICRA |= (1<<ISC00);								
	else if(edge == FALLING_EDGE)
		EICRA |= (1<<ISC01);								
	else if(edge == RISING_EDGE)
		EICRA |= (1<<ISC01) | (1<<ISC00);		

	//Enable INT0 interrupt
	EIMSK |= _BV(INT0);	

	sei();
}
void initialisationTIMER1_COMP(bool A, bool B){
	cli();
	if(A)
		TIMSK1 = _BV(OCIE1A);								//Output Compare A Match Interrupt Enable
	if(B)
		TIMSK1 = _BV(OCIE1B);								//Output Compare B Match Interrupt Enable
	sei();
}

void outputTimer1A(uint16_t duree) {
		TCNT1 = 0;											//valeur de départ du compteur
		OCR1A = duree;										//TOP value
		TCCR1B &= 0;										//Initier tout a zero (Eviter les conflits)
		TCCR1B |= (1 << CS11) | (1 << WGM12);				//CTC, prescalar de 8
}

void outputTimer1B(uint16_t duree) {
		TCNT1 = 0;											//valeur de départ du compteur
		OCR1B = duree;										//TOP value
		TCCR1B |= (1<<CS12) | (1<<CS10) | (1 << WGM12);		//CTC, prescalar de 1024
}
