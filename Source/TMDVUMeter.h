/*
  ==============================================================================

    TMDVUMeter.h
    Created: 11 Jul 2019 9:53:04am
    Author:  mcfre

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class TMDVUMeter
	:	public Component,
		public Timer
{
public:
	TMDVUMeter(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDVUMeter();

	void paint(Graphics& g)override;

	void timerCallback() override;

	void setParameterID(int inParameterID);

private:

	int mParameterID;

	float mCh0Level;
	float mCh1Level;

	TimeMachineDelayAudioProcessor* mProcessor;
};