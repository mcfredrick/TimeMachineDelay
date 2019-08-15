/*
  ==============================================================================

    TMDPanelBase.h
    Created: 4 Jul 2019 3:39:08pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

#include "PluginProcessor.h"

#include "TMDInterfaceDefines.h"

class TMDPanelBase
	:	public Component
{
public:

	TMDPanelBase(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDPanelBase();

	void mouseEnter (const MouseEvent& event) override;

	void mouseExit(const MouseEvent& event) override;

	void paint(Graphics& g) override;

protected:

	TimeMachineDelayAudioProcessor* mProcessor;
};