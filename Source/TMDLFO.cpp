/*
  ==============================================================================

    TMDLFO.cpp
    Created: 3 Jul 2019 6:03:35pm
    Author:  Matt

  ==============================================================================
*/

#include "TMDLFO.h"
#include "JuceHeader.h"

TMDLFO::TMDLFO()
{
	reset();
}

TMDLFO::~TMDLFO()
{

}

void TMDLFO::reset()
{
	mPhase = 0.0f;
	zeromem(mBuffer, sizeof(float) * maxBufferDSPSize);
}

void TMDLFO::setSampleRate(double inSampleRate)
{
	mSampleRate = inSampleRate;
}

void TMDLFO::process(float inRate, float inDepth, int inNumSamples)
{
	const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);
	
	for (int i = 0; i < inNumSamples; i++) {
		mPhase = mPhase + (rate / mSampleRate);


		if (mPhase > 1.0f) {
			mPhase -= 1.0f;
		}

		const float lfoPosition = sinf(mPhase * k2PI) * inDepth;

		mBuffer[i] = lfoPosition;
	}
}

float* TMDLFO::getBuffer()
{
	return mBuffer;
}