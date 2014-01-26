#ifndef __POLARPATTERNPROCESSOR_H
#define __POLARPATTERNPROCESSOR_H
#include "PolarPatternData.h"

class PolarPatternProcessor{
public:
	PolarPatternProcessor();
	void initialize(float sampleRate);
	void process(float* rinput, float* linput, float*output, int numberOfSamples);
	void setPolarPattern(PolarPattern type);
	void setRecType(RecType rec);
	void setProcessor();
private:
	PolarPatternData processor;
	float sampleRate;
	RecType rec;
	PolarPattern type;
};
#endif