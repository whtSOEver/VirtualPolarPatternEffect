#include "plugin.h"
#include "pluginterfaces/base/ustring.h"

#include <stdio.h>

namespace Steinberg {
namespace Vst {

//-----------------------------------------------------------------------------
// member function of PluginController!
// define parameter definitions here...
void PluginController::setupParameters(){
	// Erzeugt ein StringListParameter* Objekt mit der Bezeichnung stringListParameter
	StringListParameter* PolarPatternTypeListParameter = new StringListParameter(STR16("Microphone polar pattern:"), kPatternTypeId);
    // F�gt dem Array-Objekt die Bezeichnungen der einzelnen Richtcharakteristiken als USTRING an
	PolarPatternTypeListParameter->appendString(USTRING("Omnidirectional"));
    PolarPatternTypeListParameter->appendString(USTRING("Figure of 8"));
	PolarPatternTypeListParameter->appendString(USTRING("Subcardioid"));
	PolarPatternTypeListParameter->appendString(USTRING("Cardioid"));
	PolarPatternTypeListParameter->appendString(USTRING("Hypercardioid"));
	PolarPatternTypeListParameter->appendString(USTRING("Supercardioid"));
	// Erzeugen eines weiteren StringListParameter* Objektes, welches mit den Bezeichungen der Aufnahmeverfahren bef�llt wird
	StringListParameter* RecTypeListParameter = new StringListParameter(STR16("Recording Process:"), kRecTypeId);
	RecTypeListParameter->appendString(USTRING("2 Cardioids"));
	RecTypeListParameter->appendString(USTRING("Omnidirectional and Figure of 8"));
	// Hinzuf�gen der Parameter stringListParameter/RecTypeListParameter
	parameters.addParameter(PolarPatternTypeListParameter);
	parameters.addParameter(RecTypeListParameter);
}

//-----------------------------------------------------------------------------
Plugin::Plugin ()
: numChannels(0)
, sampleRate(0)
{
	setControllerClass (PluginControllerUID);
}
//-----------------------------------------------------------------------------
void Plugin::startProcessing(int numChannels, SampleRate sampleRate){
	this->numChannels = numChannels;
	this->sampleRate = sampleRate;
	leftProcessor.initialize(sampleRate);
	rightProcessor.initialize(sampleRate);
}
tresult PLUGIN_API Plugin::process (ProcessData& data)
{
    if (hasInputParameterChanged(data, kPatternTypeId)){
        float patterntype = getInputParameterChange(data, kPatternTypeId);
		// F�hrt die Methode min der Standardbibliothek aus und weist, �ber die Parameterver�nderung aus patterntype,
		// der Variable pptype den Entsprechenden Eintrag in dem enum-Datentyp PolarPattern zu
		PolarPattern pptype = (PolarPattern) std::min<int8> ((int8)(NUMTYPES * patterntype), NUMTYPES - 1);
		leftProcessor.setPolarPattern(pptype);
		rightProcessor.setPolarPattern(pptype);
    }
	if (hasInputParameterChanged(data, kRecTypeId)){
        float rtype = getInputParameterChange(data, kRecTypeId);
		// F�hrt die Methode min der Standardbibliothek aus und weist, �ber die Parameterver�nderung aus rtype,
		// der Variable rectype den Entsprechenden Eintrag in dem enum-Datentyp RecType zu
		RecType rectype = (RecType) std::min<int8> ((int8)(NUMTYPES2 * rtype), NUMTYPES2 -1);
		leftProcessor.setRecType(rectype);
		rightProcessor.setRecType(rectype);
    }
 	if (numChannels > 0){

	}
	if (numChannels > 1){
		// Erstellen von 4 Arrays, die mit entsprechenden Samples f�r linken und rechten Ein- sowie Ausgang bef�llt werden
		float* rightInputChannel = data.inputs[0].channelBuffers32[1];
		float* rightOutputChannel = data.outputs[0].channelBuffers32[1];
		float* leftInputChannel = data.inputs[0].channelBuffers32[0];
		float* leftOutputChannel = data.outputs[0].channelBuffers32[0];
		// F�hrt die Methode process f�r den linken und rechten Kanal aus
		rightProcessor.process(rightInputChannel, leftInputChannel, rightOutputChannel, data.numSamples);
		leftProcessor.process(rightInputChannel, leftInputChannel, leftOutputChannel, data.numSamples);
	}
	return kResultTrue;
}


}} // namespaces

