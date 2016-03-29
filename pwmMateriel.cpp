#include "pwmMateriel.h"

void ajustementPWMPourcentage (uint8_t a, uint8_t b) {	//Entre 0 et 100
TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<COM0B1); 			//pwm phase correct, top = 0xff, clear on compare match
OCR0B = a*255/100; 										//PWM sur PB3)
OCR0A = b*255/100;										//PWM sur PB4)
TCCR0B |= _BV(CS01); 									//Prescalar = 8
}

//a enlever
/*void ajustementPWM (uint8_t operande) {				//Entre 0 et 100
TCCR0A |= (1<<WGM00)|(1<<COM0A1)|(1<<COM0B1); 			//pwm phase correct, top = 0xff, clear on compare match
OCR0A = operande; 	//30								// moteur Gauche --- compte jusqu'a cette valeur là puis fait le compare match à ce point là (Pour le PWM génére à la broche 6)
OCR0B = operande; 										// moteur droit --- compte jusqu'a cette valeur là puis fait le compare match à ce point là (Pour le PWM génére à la broche 5)
TCCR0B |= _BV(CS01); 									//Prescalar = 8
}*/

void setRotation(uint16_t puissance, bool orientation){	//0 = gauche, 1 = droite
	if (orientation){									//Si droite
		PORTB |= 0b00000100; 							//Set direction = droite
		PORTB &= ~(0b00100000); 						//Set direction = droite
	}
	else{												//Si gauche
		PORTB |= 0b00100000; 							//Set direction = gauche
		PORTB &= ~(0b00000100); 						//Set direction = gauche
	}
	ajustementPWMPourcentage(puissance, puissance);
}

//a enlever
void tournerAdroite(void){
	PORTB |= 0b00000100; 								//Set direction = droite
	PORTB &= ~(0b00100000); 							//Set direction = droite 
	ajustementPWMPourcentage (100,100);
	_delay_ms(643);
	ajustementPWMPourcentage (0,0);
	}

//a enlever	
void tournerAGauche(void){
	PORTB |= 0b00100000; 								//Set direction = gauche
	PORTB &= ~(0b00000100); 							//Set direction = gauche		
	ajustementPWMPourcentage (100,100);
	_delay_ms(643);
	ajustementPWMPourcentage (0,0);
	}
	
void avancer(uint8_t operande){
	PORTB &= ~(0b00100100); 
	ajustementPWMPourcentage(operande, operande);
}
	
void arreter(void){
	ajustementPWMPourcentage (0,0);
}


