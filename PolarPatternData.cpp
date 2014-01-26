#include <math.h>
#include "PolarPatternData.h"

PolarPatternData::PolarPatternData()
	: B(0)
{}

void PolarPatternData::initialize(double setSampleRate){
	sampleRate = setSampleRate;
}

// Erzeugt die Methode setB, die als Variablen die enum-Datentypen mit den Namen PolarPattern und RecType �bermittelt bekommt
void PolarPatternData::setB(PolarPattern type, RecType rec){
	// In der ersten If-Verzweigung wird �berpr�ft, welches Aufnahmeverfahren in der gew�hlt wurde
	if (rec == CARDACARD){
		// Die zweite If-Verzweigung bestimmt, bei gew�hltem Aufnahmeverfahren, die gew�nschte Richtcharakteristik
		// und weist der variablen B, des Datentyps float, einen entsprechenden Wert zu
		if (type == OMNI){
			B = 1.0;
		}
		else if (type == FIGO8){
			B = -1.0;
		}
		else if (type == SUBCARD){
			B = 0.32;
		}
		else if (type == CARD){
			B = 0.0;
		}
		else if (type = HYPCARD){
			B = -0.5;
		}
		else if (type = SUPCARD){
			B = -0.26;
		}
	}
	else if (rec == OMNIAFIGO8){
		if (type == OMNI){
			B = 0.0;
		}
		else if (type == FIGO8){
			B = 1.0;
		}
		else if (type == SUBCARD){
			B = 0.52;
		}
		else if (type == CARD){
			B = 1;
		}
		else if (type = HYPCARD){
			B = 3;
		}
		else if (type = SUPCARD){
			B =	1.7;
		}
	}
}

// Das Eingangssample wird mit dem Faktor B multipliziert und gibt diesen Wert aus
float PolarPatternData::processOneSample(float input){
	return input * B;
}