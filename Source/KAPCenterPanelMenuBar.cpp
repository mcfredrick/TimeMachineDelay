/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 4 Jul 2019 3:40:20pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"
#include "KAPParameters.h"
KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(NewChorusFlangerAudioProcessor* inProcessor)
	:	KAPPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_MENU_BAR_WIDTH,
			CENTER_PANEL_MENU_BAR_HEIGHT);

	const int width = 85;

	//create a combo box and have it display the name of the active delay type
	mEffectsTypeComboBox = 
	new KAPParameterComboBox(mProcessor->parameters, KAPParameterID[kParameter_DelayType]);
	mEffectsTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
	mEffectsTypeComboBox->addItem("DELAY", 1);
	mEffectsTypeComboBox->addItem("CHORUS", 2);
	mEffectsTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_DelayType), 
												dontSendNotification);
	addAndMakeVisible(mEffectsTypeComboBox);
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}

void KAPCenterPanelMenuBar::addEffectsTypeComboBoxListener(ComboBox::Listener* inListener)
{
	mEffectsTypeComboBox->addListener(inListener);
}

void KAPCenterPanelMenuBar::removeEffectsTypeComboBoxListener(ComboBox::Listener* inListener)
{
	mEffectsTypeComboBox->removeListener(inListener);
}
