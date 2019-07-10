/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 4 Jul 2019 3:40:43pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPGainPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"

KAPGainPanel::KAPGainPanel(NewChorusFlangerAudioProcessor* inProcessor)
	:	KAPPanelBase(inProcessor)
{
	setSize(GAIN_PANEL_WIDTH,
			GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::paint(Graphics& g)
{
	KAPPanelBase::paint(g);

	if (mSlider) {
		paintComponentLabel(g, mSlider);
	};
}

void KAPGainPanel::setParameterID(int inParameterID)
{
	mSlider = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[inParameterID]);

	const int slider_size = 54;

	mSlider->setBounds((getWidth() * 0.5) - (slider_size * 0.5), 
					   (getHeight() * 0.5) - (slider_size * 0.5), 
					   slider_size, 
					   slider_size);

	addAndMakeVisible(mSlider);
}