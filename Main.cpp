#include <lemons_psola/lemons_psola.h>
#include <lemons_plugin/lemons_plugin.h>

namespace PsolaTest
{

using namespace lemons;

template<typename SampleType>
class Engine : public dsp::LatencyEngine<SampleType>
{
private:
    void renderChunk (const juce::AudioBuffer<SampleType>& input,
                      juce::AudioBuffer<SampleType>& output,
                      juce::MidiBuffer& midiMessages, bool isBypassed) final
    {
        output.clear();
        
        if (isBypassed)
            return;
        
        auto outRight = dsp::buffers::getAliasBuffer (output, 0, output.getNumSamples(), 1, 1);

        osc.getSamples (outRight);
        
        analyzer.analyzeInput (outRight);
        
        outRight.clear();
        
        for (const auto& m : midiMessages)
        {
            const auto message = m.getMessage();

            if (message.isNoteOn())
                shifter.setPitchHz (math::midiToFreq (message.getNoteNumber()));
        }
        
        auto outLeft = dsp::buffers::getAliasBuffer (output, 0, output.getNumSamples(), 1, 0);

        shifter.getSamples (outLeft);

        output.applyGain (0.5f);
    }
    
    void prepared (int, double samplerate, int) final
    {
        osc.setFrequency (440.f, static_cast<float>(samplerate));
        
        const auto latency = analyzer.setSamplerate (samplerate);
        
        shifter.setPitchHz (440);
        
        this->changeLatency (latency);
    }
    
    dsp::osc::Triangle<SampleType> osc;
    dsp::psola::Analyzer<SampleType> analyzer;
    dsp::psola::Shifter<SampleType> shifter { analyzer };
};

using Processor = plugin::StatelessProcessor<Engine>;

using WithEditor = plugin::ProcessorWithGenericEditor<Processor>;

}

LEMONS_DEFINE_PLUGIN_CREATOR (PsolaTest::WithEditor)
