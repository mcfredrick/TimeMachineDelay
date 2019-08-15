/*
  ==============================================================================

    TMDEffectsPanel.cpp
    Created: 4 Jul 2019 3:40:33pm
    Author:  Matt

  ==============================================================================
*/

#include "TMDEffectsPanel.h"
#include "TMDParameters.h"
#include "TMDHelperFunctions.h"

TMDEffectsPanel::TMDEffectsPanel(TimeMachineDelayAudioProcessor* inProcessor)
	:	TMDPanelBase(inProcessor)//,
		//mStyle(kTMDEffectsPanelStyle_Delay)
{
	setSize(FX_PANEL_WIDTH,
			FX_PANEL_HEIGHT);

	//set the effects panel style based on the delay type 
	//used to determine which knobs end up in the effects panel
	const int currentStyle = (int)mProcessor->getParameter(kParameter_DelayType);
	setEffectsPanelStyle((TMDEffectsPanelStyle)currentStyle);
}

TMDEffectsPanel::~TMDEffectsPanel()
{

}

void TMDEffectsPanel::paint(Graphics& g)
{
	TMDPanelBase::paint(g);

	String label;

	switch (mStyle)
	{
		case(kTMDEffectsPanelStyle_Delay): {

			label = "Delay";
		}break;

		case(kTMDEffectsPanelStyle_Chorus): {

			label = "Chorus";
		}break;
		
		default:
		case(kTMDEffectsPanelStyle_TotalNumStyles): {

			jassertfalse;
		}break;

	}

	g.setColour(TMDColour_5);
	g.setFont(font_3);

	g.drawText(label, 0, 0, getWidth(), 80, Justification::centred, 1);

	//paint labels
	for (int i = 0; i < mSliders.size(); i++) {
		paintComponentLabel(g, mSliders[i]);
	}

}

void TMDEffectsPanel::setEffectsPanelStyle(TMDEffectsPanelStyle inStyle)
{
	mStyle = inStyle;

	mSliders.clear();

	const int slider_size = 56;
	int x = 130;
	int y = (getHeight() * 0.5) - (slider_size * 0.5);

	switch (mStyle)
	{
	case(kTMDEffectsPanelStyle_Delay): {

		//construct the slider
		TMDParameterSlider* time = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[kParameter_DelayTime], TMDParameterLabel[kParameter_DelayTime]);
		time->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(time);
		//add slider to the array mSliders
		mSliders.add(time);
		//increment the x position of each knob
		x = x + (slider_size * 2);


		//construct the slider
		TMDParameterSlider* feedback = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[kParameter_DelayFeedback], TMDParameterLabel[kParameter_DelayFeedback]);
		feedback->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(feedback);
		//add slider to the array mSliders
		mSliders.add(feedback);
		//increment the x position of each knob
		x = x + (slider_size * 2);

		//construct the slider
		TMDParameterSlider* wetdry = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[kParameter_DelayWetDry], TMDParameterLabel[kParameter_DelayWetDry]);
		wetdry->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(wetdry);
		//add slider to the array mSliders
		mSliders.add(wetdry);
		//increment the x position of each knob
		x = x + (slider_size * 2);

	}break;

	case(kTMDEffectsPanelStyle_Chorus): {

		//construct the slider
		TMDParameterSlider* rate = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[kParameter_ModulationRate], TMDParameterLabel[kParameter_ModulationRate]);
		rate->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(rate);
		//add slider to the array mSliders
		mSliders.add(rate);
		//increment the x position of each knob
		x = x + (slider_size * 2);

		//construct the slider
		TMDParameterSlider* depth = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[kParameter_ModulationDepth], TMDParameterLabel[kParameter_ModulationDepth]);
		depth->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(depth);
		//add slider to the array mSliders
		mSliders.add(depth);
		//increment the x position of each knob
		x = x + (slider_size * 2);

		//construct the slider
		TMDParameterSlider* wetdry = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[kParameter_DelayWetDry], TMDParameterLabel[kParameter_DelayWetDry]);
		wetdry->setBounds(x, y, slider_size, slider_size);
		//add to the parent and make visible
		addAndMakeVisible(wetdry);
		//add slider to the array mSliders
		mSliders.add(wetdry);
		//increment the x position of each knob
		x = x + (slider_size * 2);

	}break;

	default: //if the type is undefined
	case(kTMDEffectsPanelStyle_TotalNumStyles): {
		//this shouldn't happen!

		jassertfalse;
	}break;

	}

	repaint();
}

void TMDEffectsPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	TMDEffectsPanelStyle style = (TMDEffectsPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();

	setEffectsPanelStyle(style);
}