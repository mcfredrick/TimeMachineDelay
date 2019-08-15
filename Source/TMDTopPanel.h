/*
  ==============================================================================

    TMDTopPanel.h
    Created: 4 Jul 2019 3:41:06pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "TMDPanelBase.h"

class TMDTopPanel
	: public TMDPanelBase,
	public Button::Listener,
	public ComboBox::Listener
{
public:

	TMDTopPanel(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDTopPanel();

	void paint(Graphics& g) override;

	void buttonClicked(Button*) override;

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	void displaySaveAsPopup();

	void updatePresetComboBox();

	ScopedPointer<ComboBox> mPresetDisplay;

	ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
	
};