/*
  ==============================================================================

    TMDCenterPanelMenuBar.h
    Created: 4 Jul 2019 3:40:20pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "TMDPanelBase.h"
#include "TMDParameterComboBox.h"

class TMDCenterPanelMenuBar
	: public TMDPanelBase
{
public:
	TMDCenterPanelMenuBar(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDCenterPanelMenuBar();

	void addEffectsTypeComboBoxListener(ComboBox::Listener* inListener);

	void removeEffectsTypeComboBoxListener(ComboBox::Listener* inListener);

private:

	ScopedPointer<TMDParameterComboBox> mEffectsTypeComboBox;
};