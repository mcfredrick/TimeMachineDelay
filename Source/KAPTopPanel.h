/*
  ==============================================================================

    KAPTopPanel.h
    Created: 4 Jul 2019 3:41:06pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel
	: public KAPPanelBase,
	public Button::Listener,
	public ComboBox::Listener
{
public:

	KAPTopPanel(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPTopPanel();

	void paint(Graphics& g) override;

	void buttonClicked(Button*) override;

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	void displaySaveAsPopup();

	void updatePresetComboBox();

	ScopedPointer<ComboBox> mPresetDisplay;

	ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
	
};