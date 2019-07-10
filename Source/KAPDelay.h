/*
  ==============================================================================

    KAPDelay.h
    Created: 3 Jul 2019 6:04:12pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPAudioHelpers.h"

enum KAPDelayType
{
	kKAPDelayType_Delay = 0,
	kKAPDelayType_Chorus,
};

class KAPDelay
{
public:
	KAPDelay();
	~KAPDelay();

	void setSampleRate(double inSampleRate);

	void reset();

	void process(float* inAudio,
		float inTime,
		float inFeedback,
		float inWetDry,
		float inType,
		float* inModulationBuffer,
		float* outAudio,
		int inNumSamplesToRender);

private:

	//internal
	double getInterpolatedSample(float inDelayTimeInSamples);

	double mSampleRate;
	double mBuffer[maxBufferDSPSize];
	double mFeedbackSample;

	float mTimeSmoothed;

	int mDelayIndex;

};
