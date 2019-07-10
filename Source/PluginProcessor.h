/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "KAPGain.h"
#include "KAPDelay.h"
#include "KAPLFO.h"
#include "KAPPresetManager.h"

//==============================================================================
/**
*/
class NewChorusFlangerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NewChorusFlangerAudioProcessor();
    ~NewChorusFlangerAudioProcessor();

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

	AudioProcessorValueTreeState parameters;

	KAPPresetManager* getPresetManager()
	{
		return mPresetManager;
	}

private:

	//internal
	void initializeDSP();

	//internal
	void initializeParameters();

	ScopedPointer<KAPGain> mInputGain[2];
	ScopedPointer<KAPGain> mOutputGain[2];
	ScopedPointer<KAPDelay> mDelay[2];
	ScopedPointer<KAPLFO> mLFO[2];

	ScopedPointer<KAPPresetManager> mPresetManager;

	//JUCE's ScopedPointer Class uses std::unique_ptr<KAPGain> mInputGain[2];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewChorusFlangerAudioProcessor)
};
