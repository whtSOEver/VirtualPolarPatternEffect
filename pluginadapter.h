#ifndef __pluginadapter__
#define __pluginadapter__

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
namespace Vst {


class PluginAdapter : public AudioEffect
{
public:
        PluginAdapter ();
        virtual ~PluginAdapter (){}
        virtual void startProcessing(int numChannels, SampleRate sampleRate) = 0;
        tresult PLUGIN_API initialize (FUnknown* context);
        tresult PLUGIN_API setBusArrangements (SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);
        tresult PLUGIN_API setActive (TBool state);
protected:
    bool hasInputParameterChanged(ProcessData &data, ParamID paramId);
    ParamValue getInputParameterChange(ProcessData &data, ParamID paramId);
    void setOutputParameterChange(ProcessData &data, ParamID paramId, ParamValue value);
};

//------------------------------------------------------------------------

class IParamUpdater{
public:
        virtual ~IParamUpdater(){}
        virtual void update (ParamID tag, ParamValue value) = 0;
};


//-----------------------------------------------------------------------------
class PluginController : public EditController
{
public:
        
        //---from IPluginBase--------
        tresult PLUGIN_API initialize (FUnknown* context);
        tresult PLUGIN_API terminate  ();

        //---from EditController-----
        tresult PLUGIN_API setParamNormalized (ParamID tag, ParamValue value);
        IPlugView* PLUGIN_API createView (const char* name);
        void editorDestroyed (EditorView* editor) {} // nothing to do here
        void editorAttached (EditorView* editor);
        void editorRemoved (EditorView* editor);

        //---Internal functions-------
        void addDependentView (IParamUpdater* view);
        void removeDependentView (IParamUpdater* view);

        static FUnknown* createInstance (void*) { return (IEditController*)new PluginController (); }
private:
        //---will be defined in plugin.cpp-------
        void setupParameters();
private:
        TArray <IParamUpdater*> viewsArray;
};


}} // namespaces

#endif //__plugin__