#include <avr/io.h>
#include "pwmSonore.h"

//PD7 en utilisation (Output, forcé)
//Fréquence non testée - app PitchLab lite
//On veut une fréquence entre 110Hz (Note 45) et 880Hz (Note 81)

void sonPWM (uint8_t note) {

	if (note){ 											//Si note != 0
		TCCR2A |= (1<<WGM21)|(1<<COM2A0); 				//Toggle on compare match et mode CTC, p.153, voir plus bas
		TCCR2A &= ~(1<<COM2A1);							//C'est comme ça qu'on met un bit à zero :)
		TCCR2B |= _BV(CS22) | _BV(CS21) | _BV(CS20); 	//Division d'horloge par 1024. Frequence de PWM de 7812Hz
		OCR2A = 38-(note-45);							//f(81)=4.44 et f(45)=35.5;
				
		//Pourquoi 35.5: Compter prend 1/7812 s. On veut des cycles HIGH et LOW de 4.54 ms (Voir tableau). 4.54ms/(1/7812)s = 35.5
		//Pourquoi 4.4: Compter prend 1/7812 s. On veut des cycles HIGH et LOW de 0.57 ms (Voir tableau). 0.57ms/(1/7812)s = 4.4
		//Ceci implique un toggle, et non un clear/set on compare match. (PWM de 50% tout le temps)
		
	}
	else {												//Si note = 0
		TCCR2A |= (1<<COM2A1); 							//Compteur désactivé, p.128. (Clear on compare match = no toggle)
		TCCR2A &= ~(1<<COM2A0); 						//C'est comme ça qu'on met un bit à zero :)
		OCR2A = 100;
	}
}
