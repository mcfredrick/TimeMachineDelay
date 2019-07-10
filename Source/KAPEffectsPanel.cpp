/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 4 Jul 2019 3:40:33pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPEffectsPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"

KAPEffectsPanel::KAPEffectsPanel(NewChorusFlangerAudioProcessor* inProcessor)
	:	KAPPanelBase(inProcessor)//,
		//mStyle(kKAPEffectsPanelStyle_Delay)
{
	setSize(FX_PANEL_WIDTH,
			FX_PANEL_HEIGHT);

	//set the effects panel style based on the delay type 
	//used to determine which knobs end up in the effects panel
	const int currentStyle = (int)mProcessor->getParameter(kParameter_DelayType);
	setEffectsPanelStyle((KAPEffectsPanelStyle)currentStyle);
}

KAPEffectsPanel::~KAPEffectsPanel()
{

}

void KAPEffectsPanel::paint(Graphics& g)
{
	KAPPanelBase::paint(g);

	switch (mStyle)
	{
	case(kKAPEffectsPanelStyle_Delay): {

		g.drawFittedText("Delay", 0, 0, getWidth(), getHeight() * 0.75, Justification::centred, 1);
	}break;

	case(kKAPEffectsPanelStyle_Chorus): {

		g.drawFittedText("Chorus", 0, 0, getWidth(), getHeight() * 0.75, Justification::centred, 1);
	}break;

	default: //if the type is undefined
	case(kKAPEffectsPanelStyle_TotalNumStyles): {
		//this shouldn't happen!
		g.drawFittedText("NO! Run Away!", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
		jassertfalse;
	}break;

	}

	//paint labels
	for (int i = 0; i < mSliders.size(); i++) {
		paintComponentLabel(g, mSliders[i]);
	}

}

void KAPEffectsPanel::setEffectsPanelStyle(KAPEffectsPanelStyle inStyle)
{
	mStyle = inStyle;

	mSliders.clear();

	const int slider_size = 56;
	int x = 130;
	int y = (getHeight() * 0.5) - (slider_size * 0.5);

	switch (mStyle)
	{
	case(kKAPEffectsPanelStyle_Delay): {

		//construct the slider
		KAPParameterSlider* time = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayTime]);
		time->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(time);
		//add slider to the array mSliders
		mSliders.add(time);
		//increment the x position of each knob
		x = x + (slider_size * 2);


		//construct the slider
		KAPParameterSlider* feedback = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayFeedback]);
		feedback->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(feedback);
		//add slider to the array mSliders
		mSliders.add(feedback);
		//increment the x position of each knob
		x = x + (slider_size * 2);

		//construct the slider
		KAPParameterSlider* wetdry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry]);
		wetdry->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(wetdry);
		//add slider to the array mSliders
		mSliders.add(wetdry);
		//increment the x position of each knob
		x = x + (slider_size * 2);

	}break;

	case(kKAPEffectsPanelStyle_Chorus): {

		//construct the slider
		KAPParameterSlider* rate = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationRate]);
		rate->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(rate);
		//add slider to the array mSliders
		mSliders.add(rate);
		//increment the x position of each knob
		x = x + (slider_size * 2);

		//construct the slider
		KAPParameterSlider* depth = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationDepth]);
		depth->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(depth);
		//add slider to the array mSliders
		mSliders.add(depth);
		//increment the x position of each knob
		x = x + (slider_size * 2);

		//construct the slider
		KAPParameterSlider* wetdry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry]);
		wetdry->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(wetdry);
		//add slider to the array mSliders
		mSliders.add(wetdry);
		//increment the x position of each knob
		x = x + (slider_size * 2);

	}break;

	default: //if the type is undefined
	case(kKAPEffectsPanelStyle_TotalNumStyles): {
		//this shouldn't happen!

		jassertfalse;
	}break;

	}

	repaint();
}

void KAPEffectsPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	KAPEffectsPanelStyle style = (KAPEffectsPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();

	setEffectsPanelStyle(style);
}