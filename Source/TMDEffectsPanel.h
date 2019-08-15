/*
  ==============================================================================

    TMDEffectsPanel.h
    Created: 4 Jul 2019 3:40:33pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "TMDPanelBase.h"
#include "TMDParameterSlider.h"

enum TMDEffectsPanelStyle
{
	kTMDEffectsPanelStyle_Delay,
	kTMDEffectsPanelStyle_Chorus,
	kTMDEffectsPanelStyle_TotalNumStyles
};

class TMDEffectsPanel
	: public TMDPanelBase,
	public ComboBox::Listener
{
public:

	TMDEffectsPanel(TimeMachineDelayAudioProcessor* inProcessor);
	~TMDEffectsPanel();

	void paint(Graphics& g) override;

	void setEffectsPanelStyle(TMDEffectsPanelStyle inStyle);

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	TMDEffectsPanelStyle mStyle;

	OwnedArray<TMDParameterSlider> mSliders;
};