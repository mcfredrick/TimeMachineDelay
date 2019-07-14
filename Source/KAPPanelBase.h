/*
  ==============================================================================

    KAPPanelBase.h
    Created: 4 Jul 2019 3:39:08pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

#include "PluginProcessor.h"

#include "KAPInterfaceDefines.h"

class KAPPanelBase
	:	public Component
{
public:

	KAPPanelBase(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPPanelBase();

	void mouseEnter (const MouseEvent& event) override;

	void mouseExit(const MouseEvent& event) override;

	void paint(Graphics& g) override;

protected:

	NewChorusFlangerAudioProcessor* mProcessor;
};