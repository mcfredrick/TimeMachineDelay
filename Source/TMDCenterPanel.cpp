/*
  ==============================================================================

    TMDCenterPanel.cpp
    Created: 4 Jul 2019 3:39:58pm
    Author:  Matt

  ==============================================================================
*/

#include "TMDCenterPanel.h"

TMDCenterPanel::TMDCenterPanel(TimeMachineDelayAudioProcessor* inProcessor)
	:	TMDPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_WIDTH,
			CENTER_PANEL_HEIGHT);

	mMenuBar = new TMDCenterPanelMenuBar(inProcessor);
	mMenuBar->setTopLeftPosition(0, 0);
	addAndMakeVisible(mMenuBar);

	mFxPanel = new TMDEffectsPanel(inProcessor);
	mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
	addAndMakeVisible(mFxPanel);

	mMenuBar->addEffectsTypeComboBoxListener(mFxPanel);
}

TMDCenterPanel::~TMDCenterPanel()
{
	mMenuBar->removeEffectsTypeComboBoxListener(mFxPanel);
}