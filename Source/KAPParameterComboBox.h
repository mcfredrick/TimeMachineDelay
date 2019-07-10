/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 5 Jul 2019 12:02:35pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "JUCEHeader.h"

class KAPParameterComboBox
	: public ComboBox
{
public:

	KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID);

	~KAPParameterComboBox();

private:

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterComboBox);
};