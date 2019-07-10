/*
  ==============================================================================

    KAPLFO.h
    Created: 3 Jul 2019 6:03:35pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "KAPAudioHelpers.h"

class KAPLFO
{
public:
	KAPLFO();
	~KAPLFO();

	void reset();

	void setSampleRate(double inSampleRate);

	void process(float inRate, float inDepth, int inSamples);

	float* getBuffer();

private:
	double mSampleRate;

	float mPhase;

	float mBuffer[maxBufferDSPSize];

};