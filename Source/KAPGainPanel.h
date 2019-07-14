/*
  ==============================================================================

    KAPGainPanel.h
    Created: 4 Jul 2019 3:40:43pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"
#include "KAPVUMeter.h"

class KAPGainPanel
	:	public KAPPanelBase
{
public:
	
	KAPGainPanel(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPGainPanel();

	void paint(Graphics& g) override;

	void setParameterID(int inParameterID);

private:

	ScopedPointer<KAPVUMeter> mVUMeter;
	ScopedPointer<KAPParameterSlider> mSlider;
};