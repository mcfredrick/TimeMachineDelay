/*
  ==============================================================================

    KAPMainPanel.h
    Created: 4 Jul 2019 3:39:23pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPTopPanel.h"
#include "KAPGainPanel.h"
#include "KAPCenterPanel.h"

class KAPMainPanel
	:	public KAPPanelBase
{
public:

	KAPMainPanel(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPMainPanel();

private:

	ScopedPointer<KAPTopPanel> mTopPanel;
	ScopedPointer<KAPGainPanel> mInputGainPanel;
	ScopedPointer<KAPGainPanel> mOutputGainPanel;
	ScopedPointer<KAPCenterPanel> mCenterPanel;
};