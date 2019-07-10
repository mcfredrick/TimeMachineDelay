/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 5 Jul 2019 12:02:14pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "JUCEHeader.h"

class KAPParameterSlider
	: public Slider
{
public:

	KAPParameterSlider(AudioProcessorValueTreeState& stateToControl,
					   const String& parameterID);

	~KAPParameterSlider();

private:

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterSlider);
};