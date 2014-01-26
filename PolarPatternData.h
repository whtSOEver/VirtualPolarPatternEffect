#ifndef __POLARPATTERNDATA_H
#define __POLARPATTERNDATA_H
#include <string>

// erzeugt einen enum Datentyp mit dem Namen PolarPattern, welcher die Richtcharaktersitiken beinhalten soll
enum PolarPattern{
	OMNI,
	FIGO8,
	SUBCARD,
	CARD,
	HYPCARD,
	SUPCARD,
	NUMTYPES
};
// erzeugt einen enum Datentyp mit dem Namen RecType, welcher die Aufnahmeart beinhalten soll
enum RecType{
	CARDACARD,
	OMNIAFIGO8,
	NUMTYPES2
};

class PolarPatternData{
public:
	PolarPatternData();
	void initialize(double sampleRate);
	void setB(PolarPattern type, RecType rec);
	float processOneSample(float input);
private:
	double sampleRate;
	float B;
};
#endif