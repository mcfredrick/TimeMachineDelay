/*
  ==============================================================================

    TMDParameterSlider.h
    Created: 5 Jul 2019 12:02:14pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "JUCEHeader.h"

class TMDParameterSlider
	: public Slider
{
public:

	TMDParameterSlider(AudioProcessorValueTreeState& stateToControl,
					   const String& parameterID,
					   const String& parameterLabel);

	~TMDParameterSlider();

private:

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TMDParameterSlider);
};