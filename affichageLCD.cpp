#include "affichageLCD.h"

void afficherLCD(uint8_t message){
	LCM LCD(&DEMO_DDR, &DEMO_PORT);

	switch (message)
	{
	case 0: 
		LCD.clear();
		break;
	//Cas pour suiveur
	case 1:
		LCD = "     Ligne 1    ";
		break;
	case 2:
		LCD = "     Ligne 2    ";
		break;
	case 3:
		if (coupureligne3 == 0)
			LCD = "     Ligne 3    ";
		if (coupureligne3 == 1)
			LCD = "     Ligne 3       Coupure  1   ";
		break;
	case 4:
		LCD = "     Ligne 4    ";
		break;
	case 5:
		LCD = "     Ligne 5    ";
		break;
	case 6:
		LCD = "     Ligne 6    ";
		break;
	case 7:
		LCD = "     Ligne 7    ";
		break;
	case 8:
		LCD = "     Ligne 8    ";
		break;
	case 9:
		if (ligneADroite9 == 0)
			LCD = "     Ligne 9    ";
		if (ligneADroite9 == 1)
			LCD = "     Ligne 9       Angle 90  1   ";
		break;
	case 10:
		LCD = "     Ligne 10    ";
		break;
	case 11:
		LCD << "           G";
		break;
	case 12:
		LCD << "            D";
		break;
	case 13:
		LCD << "    90 a gauche";
		break;
	case 14:
		LCD << "    90 a droite";
		break;
	case 15:
		LCD << "    Ligne detectee";
		break;
	case 16:
		LCD = "     Tache 3";
		break;
	//Cas pour selecteurDeTache
	case 21:
		LCD = "        1";
		break;
	case 22:
		LCD = "        2";
		break;
	case 23:
		LCD = "        3";
		break;
	case 24:
		LCD = "    ETAPE  1      Confirmation";
		break;
	case 25:
		LCD = "    ETAPE  2      Confirmation";
		break;
	case 26:
		LCD = "    ETAPE  3      Confirmation";
		break;
	//Cas pour recommencer
	case 30:
		LCD = "        Terminer";
		break;
	case 31:
		LCD = "        Recommencer";
		break;
	case 32:
		LCD = "    TERMINER      Confirmation";
		break;
	case 33:
		LCD = " RECOMMENCER      Confirmation";
	//Message de fin
	case 100:
		LCD = "  Equipe  3363  ";
		break;
	}
}
