///////////////////////////////////////////////////////////////////
//																 //
//	Pin usage:													 //
//																 //
//	PD2: INT0 interrupt pin										 //
//	--->Calculer echo, echo is white							 //
//	PD5: Trigger output pin										 //
//	--->Trigger is blue											 //
//	PD6: OC1A (Timer/Counter1 Output Compare Match A Output)	 //
//	--->partirTimer(temps)										 //
//	PB3: OC0A (Timer/Counter0 Output Compare Match A Output)	 //
//	--->Moteur                                                   //
//	PB4: OC0B (Timer/Counter0 Output Compare Match B Output)     //
//	--->Moteur                                                   //
//																 //
///////////////////////////////////////////////////////////////////

#include "etape3.h"

//Variables globales
volatile bool echoSent = 0;								//Indique si echo a été lancé
volatile bool retrigger = 0;							//Indique si on est pret à activer le trigger
volatile uint8_t nbFois = 0;							//120 fois = 8 secondes
volatile bool direction = 0;							//1 = droite
volatile bool fini = false;								//Fini après 16 secondes

ISR (INT0_vect){										//Réagit à echo
	if(!echoSent){
		EIFR |= (1 << INTF0);
		echoSent = 1;
		outputTimer1A(30000);
	}
	else {
		uint16_t distance = TCNT1;						
		if (distance/148 > 24){									//Convert to inches (24 pouces = 696 uS)
			arreter();
			PORTB &= ~(0b11000000);
			PORTB |= 0b01000000;								//DEL verte
		}
		else {
			uint16_t puissance = (101.5277778- (distance*11/720));	//Retourne entre 0 et 100 pour echo [100, 1776]
			setRotation(puissance, direction);					//Ajuster la vitesse de rotation
			PORTB &= ~(0b11000000);
			PORTB |= 0b10000000;								//DEL rouge
		}
		nbFois++;
		EIFR |= (1 << INTF0);
		echoSent = 0;
		retrigger = 0;
	}
	
}

ISR(TIMER1_COMPA_vect){									//Réagit aux délais
	if (echoSent){
		PORTB &= ~(0b11000000);
		PORTB |= 0b01000000;							//DEL verte
		arreter();										//Stop
		nbFois++;
		echoSent = 0;
		retrigger = 0;
	}
	if (!retrigger){
		outputTimer1A(36666);							//Attente du prochain trigger
		retrigger = 1;
	}
	else{
		if (nbFois < 120){								//Moins de 8 secondes
			direction = DROITE;							//Sens horaire (droite)
			PORTD |= 0b00010000;						//Set PD4 to 1 (Start trigger)
			_delay_us(10);		
			PORTD &= ~(0b00010000);						//Set PD4 to 0 (Stop trigger)
		}
		else if (nbFois < 240){							//Moins de 16 secondes
			direction = GAUCHE;							//Sens anti-horaire (gauche)
			PORTD |= 0b00010000;						//Set PD4 to 1 (Start trigger)
			_delay_us(10);		
			PORTD &= ~(0b00010000);						//Set PD4 to 0 (Stop trigger)
		}
		else
			fini = true;
	}
}

void etape3(){	
	initialisationINT0(ANY_EDGE);							//Any edge
	initialisationTIMER1_COMP(true, false);					//Set COMPA
	
	//Émettre un son aigu d'une durée de 2 secondes
	sonPWM(75);
	_delay_ms(2000);
	sonPWM(0);
	
	//Premier trigger manuel
	PORTD |= 0b00010000;						
	_delay_us(10);		
	PORTD &= ~(0b00010000);						
	
	while (!fini){
		if (PINA & 0b00001000)							//U1
			sonPWM(60);
		else if (PINA & 0b00000100)						//U2
			sonPWM(62);
		else if (PINA & 0b00100000)						//U3
			sonPWM(64);
		else if (PINA & 0b00010000)						//U4
			sonPWM(65);
		else if (PINA & 0b10000000)						//U5
			sonPWM(67);
		else											//No pin
			sonPWM(0);
	}
	sonPWM(0);
	PORTB &= ~(0b11000000);								//DEL off
	arreter();

	afficherLCD(100);
	_delay_ms(1000)
}
