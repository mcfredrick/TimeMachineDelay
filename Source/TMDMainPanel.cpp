/*
  ==============================================================================

    TMDMainPanel.cpp
    Created: 4 Jul 2019 3:39:23pm
    Author:  Matt

  ==============================================================================
*/

#include "TMDMainPanel.h"
#include "TMDParameters.h"

TMDMainPanel::TMDMainPanel(TimeMachineDelayAudioProcessor* inProcessor)
	: TMDPanelBase(inProcessor)
{
	setSize(MAIN_PANEL_WIDTH, 
			MAIN_PANEL_HEIGHT);

	mTopPanel = new TMDTopPanel(inProcessor);
	mTopPanel->setTopLeftPosition(0, 0);
	addAndMakeVisible(mTopPanel);

	mInputGainPanel = new TMDGainPanel(inProcessor);
	mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
	mInputGainPanel->setParameterID(kParameter_InputGain);
	addAndMakeVisible(mInputGainPanel);

	mOutputGainPanel = new TMDGainPanel(inProcessor);
	mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	mOutputGainPanel->setParameterID(kParameter_OutputGain);
	addAndMakeVisible(mOutputGainPanel);

	mCenterPanel = new TMDCenterPanel(inProcessor);
	mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	addAndMakeVisible(mCenterPanel);
}

TMDMainPanel::~TMDMainPanel()
{

}