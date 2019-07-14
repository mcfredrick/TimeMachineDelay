/*
  ==============================================================================

    KAPGain.cpp
    Created: 3 Jul 2019 6:03:52pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPGain.h"

#include "KAPAudioHelpers.h"

KAPGain::KAPGain() //constructor
	:	mOutputSmoothed(0)
	{

	}

	KAPGain::~KAPGain()	//destructor
	{

	}

	void KAPGain::process(float* inAudio,
						  float inGain,
						  float* outAudio,
						  int inNumSamplesToRender)
	{
		float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
		gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f);
	
		for (int i = 0; i < inNumSamplesToRender; i++) {
			outAudio[i] = inAudio[i] * gainMapped;
		};

		//for VU Meter
		float absValue = fabs(outAudio[0]);
		mOutputSmoothed = kMeterSmoothingCoeff * (mOutputSmoothed - absValue) + absValue;
	}

	float KAPGain::getMeterLevel()
	{
		return mOutputSmoothed;
	}