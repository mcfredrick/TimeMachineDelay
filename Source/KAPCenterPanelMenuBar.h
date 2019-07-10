/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 4 Jul 2019 3:40:20pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterComboBox.h"

class KAPCenterPanelMenuBar
	: public KAPPanelBase
{
public:
	KAPCenterPanelMenuBar(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPCenterPanelMenuBar();

	void addEffectsTypeComboBoxListener(ComboBox::Listener* inListener);

	void removeEffectsTypeComboBoxListener(ComboBox::Listener* inListener);

private:

	ScopedPointer<KAPParameterComboBox> mEffectsTypeComboBox;
};