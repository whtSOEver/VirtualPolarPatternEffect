#ifndef __plugin__
#define __plugin__
#include "pluginadapter.h"
#include "PolarPatternProcessor.h"

namespace Steinberg {
namespace Vst {

// change these numbers!
// every plugin needs a unique UID
static const FUID PluginProcessorUID (0x89E7AE5F, 0x92554E53, 0x96FAE413, 0x3C935A18);
static const FUID PluginControllerUID (0xD39D5B65, 0xD8AF42FA, 0x143F2AC8, 0x41EB04F0);

// define parameter tags here:
enum
{
	/** parameter ID */
	kPatternTypeId = 0,
	kRecTypeId
};


class Plugin : public PluginAdapter
{
public:
	Plugin ();
	virtual ~Plugin (){}
	tresult PLUGIN_API process (ProcessData& data);
	void startProcessing(int numChannels, SampleRate sampleRate);	
	static FUnknown* createInstance (void*) { return (IAudioProcessor*)new Plugin (); }
private:
	int numChannels;
	SampleRate sampleRate;
private:
	PolarPatternProcessor leftProcessor;
	PolarPatternProcessor rightProcessor;
};




}} // namespaces

#endif //__plugin__
