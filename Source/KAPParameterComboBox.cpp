/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 5 Jul 2019 12:02:35pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID)
	: juce::ComboBox(parameterID)
{
	mAttachment =
		new AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl, parameterID, *this);
}

KAPParameterComboBox::~KAPParameterComboBox()
{

}