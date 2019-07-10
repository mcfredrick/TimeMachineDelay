/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 4 Jul 2019 3:39:58pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPCenterPanelMenuBar.h"
#include "KAPEffectsPanel.h"

class KAPCenterPanel
	: public KAPPanelBase
{
public:
	KAPCenterPanel(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPCenterPanel();

private:

	ScopedPointer<KAPCenterPanelMenuBar> mMenuBar;
	ScopedPointer<KAPEffectsPanel> mFxPanel;
};