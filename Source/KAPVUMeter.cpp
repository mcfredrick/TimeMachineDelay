/*
  ==============================================================================

    KAPVUMeter.cpp
    Created: 11 Jul 2019 9:53:04am
    Author:  mcfre

  ==============================================================================
*/

#include "KAPVUMeter.h"
#include "KAPInterfaceDefines.h"
#include "KAPParameters.h"
#include "KAPAudioHelpers.h"

KAPVUMeter::KAPVUMeter(NewChorusFlangerAudioProcessor* inProcessor)
	:	mParameterID(-1),
		mCh0Level(0),
		mCh1Level(0),
		mProcessor(inProcessor)
{

}

KAPVUMeter::~KAPVUMeter()
{

}

void KAPVUMeter::paint(Graphics& g)
{
	const int meter_width = getParentWidth() / 5;

	//set meter background color
	g.setColour(KAPColour_6);
	//left channel meter
	g.fillRect(0, 0, meter_width, getHeight());

	//right channel meter
	g.fillRect(meter_width * 2, 0, meter_width, getHeight());

	int ch0fill = getHeight() - (getHeight() * mCh0Level);
	int ch1fill = getHeight() - (getHeight() * mCh1Level);

	if (ch0fill < 0) {
		ch0fill = 0;
	}

	if (ch0fill < 0) {
		ch0fill = 0;
	}

	//set meter fill color
	g.setColour(KAPColour_glow);
	//left channel meter
	g.fillRect(0, ch0fill, meter_width, getHeight());
	//right channel meter
	g.fillRect(meter_width * 2, ch1fill, meter_width, getHeight());
}

void KAPVUMeter::timerCallback()
{
	float updatedCh0Level = 0.0f;
	float updatedCh1Level = 0.0f;

	switch (mParameterID)
	{
		case(kParameter_InputGain): {

			updatedCh0Level = mProcessor->getInputGainMeterLevel(0);
			updatedCh1Level = mProcessor->getInputGainMeterLevel(1);

		} break;

		case(kParameter_OutputGain): {

			updatedCh0Level = mProcessor->getOutputGainMeterLevel(0);
			updatedCh1Level = mProcessor->getOutputGainMeterLevel(1);

		} break;

	}

	//smooth the levels
	if (updatedCh0Level > mCh0Level) {
		mCh0Level = updatedCh0Level;
	} else {
		mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updatedCh0Level) + updatedCh0Level;
	}

	if (updatedCh1Level > mCh1Level) {
		mCh1Level = updatedCh1Level;
	} else {
		mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updatedCh1Level) + updatedCh1Level;
	}

	//set really small values equal to zero to avoid unnecessary repainting
	mCh0Level = kap_denormalize(mCh0Level);
	mCh1Level = kap_denormalize(mCh1Level);

	//repaint if either of the values are nonzero
	if (mCh0Level && mCh1Level) {
		repaint();
	}

}

void KAPVUMeter::setParameterID(int inParameterID)
{
	mParameterID = inParameterID;

	startTimerHz(15);
}