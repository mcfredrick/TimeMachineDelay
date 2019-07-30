/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "KAPLookAndFeel.h"

//==============================================================================
NewChorusFlangerAudioProcessorEditor::NewChorusFlangerAudioProcessorEditor (NewChorusFlangerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (MAIN_PANEL_WIDTH,
			 MAIN_PANEL_HEIGHT);

	mMainPanel = new KAPMainPanel(&processor);
	addAndMakeVisible(mMainPanel);
	
	//set the lookAndFeel for the editor
	mLookAndFeel = new KAPLookAndFeel();
	setLookAndFeel(mLookAndFeel);

	//set the default lookAndFeel for the program to the custom lookAndFeel
	LookAndFeel::setDefaultLookAndFeel(mLookAndFeel);

	//mBackgroundImage = ImageCache::getFromMemory(BinaryData::kadenze_bg_png, BinaryData::kadenze_bg_pngSize);
	mBackgroundImage = ImageCache::getFromMemory(BinaryData::whiteBG_png, BinaryData::whiteBG_pngSize);
	
}

NewChorusFlangerAudioProcessorEditor::~NewChorusFlangerAudioProcessorEditor()
{
}

//==============================================================================
void NewChorusFlangerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void NewChorusFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
