/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "KAPMainPanel.h"
#include "KAPLookAndFeel.h"

//==============================================================================
/**
*/
class NewChorusFlangerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    NewChorusFlangerAudioProcessorEditor (NewChorusFlangerAudioProcessor&);
    ~NewChorusFlangerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewChorusFlangerAudioProcessor& processor;

	ScopedPointer<KAPMainPanel> mMainPanel;
	ScopedPointer<KAPLookAndFeel> mLookAndFeel;

	Image mBackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewChorusFlangerAudioProcessorEditor)
};
