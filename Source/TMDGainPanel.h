/*
  ==============================================================================

    TMDGainPanel.h
    Created: 4 Jul 2019 3:40:43pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "TMDPanelBase.h"
#include "TMDParameterSlider.h"
#include "TMDVUMeter.h"

class TMDGainPanel
	:	public TMDPanelBase
{
public:
	
	TMDGainPanel(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDGainPanel();

	void paint(Graphics& g) override;

	void setParameterID(int inParameterID);

private:

	ScopedPointer<TMDVUMeter> mVUMeter;
	ScopedPointer<TMDParameterSlider> mSlider;
};