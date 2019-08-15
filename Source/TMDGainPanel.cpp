/*
  ==============================================================================

    TMDGainPanel.cpp
    Created: 4 Jul 2019 3:40:43pm
    Author:  Matt

  ==============================================================================
*/

#include "TMDGainPanel.h"
#include "TMDParameters.h"
#include "TMDHelperFunctions.h"

TMDGainPanel::TMDGainPanel(TimeMachineDelayAudioProcessor* inProcessor)
	:	TMDPanelBase(inProcessor)
{
	setSize(GAIN_PANEL_WIDTH,
			GAIN_PANEL_HEIGHT);

	const int meter_width = 64;
	mVUMeter = new TMDVUMeter(mProcessor);
	mVUMeter->setBounds((getWidth()*0.5)-(meter_width*0.5), 
						(getHeight() * 0.55) - (meter_width*0.5), 
						meter_width, 
						getHeight()*0.45);

	addAndMakeVisible(mVUMeter);
}

TMDGainPanel::~TMDGainPanel()
{

}

void TMDGainPanel::paint(Graphics& g)
{
	TMDPanelBase::paint(g);

	if (mSlider) {
		paintComponentLabel(g, mSlider);
	};
}

void TMDGainPanel::setParameterID(int inParameterID)
{
	mSlider = new TMDParameterSlider(mProcessor->parameters, TMDParameterID[inParameterID], TMDParameterLabel[inParameterID]);

	const int slider_size = 54;

	mSlider->setBounds((getWidth() * 0.5) - (slider_size * 0.5), 
					   (getHeight() * 0.20) - (slider_size * 0.5) - 10, 
					   slider_size, 
					   slider_size);

	addAndMakeVisible(mSlider);

	mVUMeter->setParameterID(inParameterID);
}