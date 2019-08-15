/*
  ==============================================================================

    TMDMainPanel.h
    Created: 4 Jul 2019 3:39:23pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "TMDPanelBase.h"

#include "TMDTopPanel.h"
#include "TMDGainPanel.h"
#include "TMDCenterPanel.h"

class TMDMainPanel
	:	public TMDPanelBase
{
public:

	TMDMainPanel(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDMainPanel();

private:

	ScopedPointer<TMDTopPanel> mTopPanel;
	ScopedPointer<TMDGainPanel> mInputGainPanel;
	ScopedPointer<TMDGainPanel> mOutputGainPanel;
	ScopedPointer<TMDCenterPanel> mCenterPanel;
};