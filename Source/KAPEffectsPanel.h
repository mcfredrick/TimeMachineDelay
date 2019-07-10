/*
  ==============================================================================

    KAPEffectsPanel.h
    Created: 4 Jul 2019 3:40:33pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"

enum KAPEffectsPanelStyle
{
	kKAPEffectsPanelStyle_Delay,
	kKAPEffectsPanelStyle_Chorus,
	kKAPEffectsPanelStyle_TotalNumStyles
};

class KAPEffectsPanel
	: public KAPPanelBase,
	public ComboBox::Listener
{
public:

	KAPEffectsPanel(NewChorusFlangerAudioProcessor* inProcessor);
	~KAPEffectsPanel();

	void paint(Graphics& g) override;

	void setEffectsPanelStyle(KAPEffectsPanelStyle inStyle);

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	KAPEffectsPanelStyle mStyle;

	OwnedArray<KAPParameterSlider> mSliders;
};