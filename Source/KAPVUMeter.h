/*
  ==============================================================================

    KAPVUMeter.h
    Created: 11 Jul 2019 9:53:04am
    Author:  mcfre

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class KAPVUMeter
	:	public Component,
		public Timer
{
public:
	KAPVUMeter(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPVUMeter();

	void paint(Graphics& g)override;

	void timerCallback() override;

	void setParameterID(int inParameterID);

private:

	int mParameterID;

	float mCh0Level;
	float mCh1Level;

	NewChorusFlangerAudioProcessor* mProcessor;
};