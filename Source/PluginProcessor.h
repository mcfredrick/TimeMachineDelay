/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TMDGain.h"
#include "TMDDelay.h"
#include "TMDLFO.h"
#include "TMDPresetManager.h"

//==============================================================================
/**
*/
class TimeMachineDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TimeMachineDelayAudioProcessor();
    ~TimeMachineDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	float getInputGainMeterLevel(int inChannel);
	float getOutputGainMeterLevel(int inChannel);

	AudioProcessorValueTreeState parameters;

	TMDPresetManager* getPresetManager()
	{
		return mPresetManager.get();
	}

private:

	//internal
	void initializeDSP();

	//internal
	void initializeParameters();

	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	std::unique_ptr<TMDGain> mInputGain[2];
	std::unique_ptr<TMDGain> mOutputGain[2];
	std::unique_ptr<TMDDelay> mDelay[2];
	std::unique_ptr<TMDLFO> mLFO[2];

	std::unique_ptr<TMDPresetManager> mPresetManager;

	//JUCE's ScopedPointer Class uses std::unique_ptr<>
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeMachineDelayAudioProcessor)
};
