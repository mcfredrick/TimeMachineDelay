/*
  ==============================================================================

    TMDCenterPanel.h
    Created: 4 Jul 2019 3:39:58pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "TMDPanelBase.h"

#include "TMDCenterPanelMenuBar.h"
#include "TMDEffectsPanel.h"

class TMDCenterPanel
	: public TMDPanelBase
{
public:
	TMDCenterPanel(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDCenterPanel();

private:

	ScopedPointer<TMDCenterPanelMenuBar> mMenuBar;
	ScopedPointer<TMDEffectsPanel> mFxPanel;
};