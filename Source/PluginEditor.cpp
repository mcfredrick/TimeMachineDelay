/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "TMDLookAndFeel.h"

//==============================================================================
TimeMachineDelayAudioProcessorEditor::TimeMachineDelayAudioProcessorEditor (TimeMachineDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (MAIN_PANEL_WIDTH,
			 MAIN_PANEL_HEIGHT);

	mMainPanel = new TMDMainPanel(&processor);
	addAndMakeVisible(mMainPanel);
	
	//set the lookAndFeel for the editor
	mLookAndFeel = new TMDLookAndFeel();
	setLookAndFeel(mLookAndFeel);

	//set the default lookAndFeel for the program to the custom lookAndFeel
	LookAndFeel::setDefaultLookAndFeel(mLookAndFeel);

	//mBackgroundImage = ImageCache::getFromMemory(BinaryData::kadenze_bg_png, BinaryData::kadenze_bg_pngSize);
	mBackgroundImage = ImageCache::getFromMemory(BinaryData::whiteBG_png, BinaryData::whiteBG_pngSize);
	
}

TimeMachineDelayAudioProcessorEditor::~TimeMachineDelayAudioProcessorEditor()
{
}

//==============================================================================
void TimeMachineDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void TimeMachineDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
