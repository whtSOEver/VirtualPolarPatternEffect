#include "PolarPatternProcessor.h"

PolarPatternProcessor::PolarPatternProcessor()
: type(OMNI),
  rec(CARDACARD)
{}

// Übermittelt die Samplerate an das Objekt processor des Datentyps PolarPatternData und führt die Methode setProcessor() aus
void PolarPatternProcessor::initialize(float sampleRate){
	this->sampleRate = sampleRate;
	processor.initialize(sampleRate);
	setProcessor();
}

// Weist der privaten Variablen type den Wert type zu und führt die Methode setPorcessor() aus
void PolarPatternProcessor::setPolarPattern(PolarPattern type){
	this->type = type;
	setProcessor();
}

// Weist der orivaten Variablen rec den Wert rec zu und führt due Methode setProcessor() aus
void PolarPatternProcessor::setRecType(RecType rec){
	this->rec = rec;
	setProcessor();
}

// Führt die Methode setB(...) des Objectes processor aus und übermittelt dabei das gewählte Aufnahmeverfahren und die Richtcharakteristik
void PolarPatternProcessor::setProcessor(){
	processor.setB(type, rec);
}

// Durchläuft die for-Schleife so oft, wie es die Variable numberOfSamples übermittelt
// Jedes Sample des Arrays rinput wird hierbei mit dem Faktor B aus PolarPatternData multipliziert und zu dem enstsprechenden Sample aus linput addiert
// Die Summe der beiden Samples wird anschließend in dem Array output gespeichert
void PolarPatternProcessor::process(float* rinput, float* linput, float*output, int numberOfSamples){
	for(int i = 0; i < numberOfSamples; i++){
		output[i] = (0.5*linput[i] + 0.5*processor.processOneSample(rinput[i]));
	}
}