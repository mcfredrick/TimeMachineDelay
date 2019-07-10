/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 4 Jul 2019 3:39:58pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPCenterPanel.h"

KAPCenterPanel::KAPCenterPanel(NewChorusFlangerAudioProcessor* inProcessor)
	:	KAPPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_WIDTH,
			CENTER_PANEL_HEIGHT);

	mMenuBar = new KAPCenterPanelMenuBar(inProcessor);
	mMenuBar->setTopLeftPosition(0, 0);
	addAndMakeVisible(mMenuBar);

	mFxPanel = new KAPEffectsPanel(inProcessor);
	mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
	addAndMakeVisible(mFxPanel);

	mMenuBar->addEffectsTypeComboBoxListener(mFxPanel);
}

KAPCenterPanel::~KAPCenterPanel()
{
	mMenuBar->removeEffectsTypeComboBoxListener(mFxPanel);
}