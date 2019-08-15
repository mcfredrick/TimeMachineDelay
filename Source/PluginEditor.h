/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "TMDMainPanel.h"
#include "TMDLookAndFeel.h"

//==============================================================================
/**
*/
class TimeMachineDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TimeMachineDelayAudioProcessorEditor (TimeMachineDelayAudioProcessor&);
    ~TimeMachineDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TimeMachineDelayAudioProcessor& processor;

	ScopedPointer<TMDMainPanel> mMainPanel;
	ScopedPointer<TMDLookAndFeel> mLookAndFeel;

	Image mBackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeMachineDelayAudioProcessorEditor)
};
