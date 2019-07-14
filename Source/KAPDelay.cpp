/*
  ==============================================================================

    KAPDelay.cpp
    Created: 3 Jul 2019 6:04:12pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPDelay.h"
#include "JuceHeader.h"
#include "KAPAudioHelpers.h"

KAPDelay::KAPDelay()
:	mSampleRate(-1), //stop the program if the sample rate isn't properly set
	mFeedbackSample(0.0),
	mTimeSmoothed(0),
	mDelayIndex(0),
	mBuffer()
	
{

}

KAPDelay::~KAPDelay() 
{

}

void KAPDelay::setSampleRate(double inSampleRate)
{
	mSampleRate = inSampleRate;
}

void KAPDelay::reset()
{
	mTimeSmoothed = 0.0f;
	zeromem(mBuffer, (sizeof(double) * maxBufferDSPSize));
}

void KAPDelay::process(float* inAudio,
					   float inTime,
					   float inFeedback,
					   float inWetDry,
					   float inType,
					   float* inModulationBuffer,
					   float* outAudio,
					   int inNumSamplesToRender)
{
	//inType initializes to 0.5 by default
	//casting it to an int truncates the value
	//without this workaround, you had to select delay explicitly in the combo box before feedback would be introduced

	DBG("inType" << (String)inType);
	const float wet = inWetDry;
	const float dry = 1.0f - wet;
	//when the delay type is set to "Delay", map the feedback parameter to the specified range
	//otherwise, (in "Chorus" mode) the feedback parameter will always be 0.
	const float feedbackMapped = 
		//inType must be cast to an int to evaluate correctly here
		((int)inType==kKAPDelayType_Delay) ? jmap(inFeedback, 0.0f, 1.0f, 0.0f, 1.20f) : 0.f;

	for (int i = 0; i < inNumSamplesToRender; i++) {
		
		if ((int)inType == kKAPDelayType_Delay) {
			//delay
			mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime);
		} else {
			//chorus
			const double delayTimeModulation = (0.003 + (.002 * inModulationBuffer[i]));

			mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation);
		}

		const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
		
		const double sample = getInterpolatedSample(delayTimeInSamples);
		
		mBuffer[mDelayIndex] = tanh_clip(inAudio[i] + (mFeedbackSample * feedbackMapped));

		mFeedbackSample = sample;

		outAudio[i] = (inAudio[i] * dry + sample * wet);

		mDelayIndex++;

		if (mDelayIndex >= maxBufferDSPSize) {
			mDelayIndex -= maxBufferDSPSize;
		}
	}
}

double KAPDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
	double readPosition = (double)mDelayIndex - inDelayTimeInSamples;

	if (readPosition < 0.0f) {
		readPosition += maxBufferDSPSize;
	}

	int index_y0 = (int)readPosition - 1;

	if (index_y0 <= 0) {
		index_y0 += maxBufferDSPSize;
	}

	int index_y1 = readPosition;

	if (index_y1 > maxBufferDSPSize) {
		index_y1 -= maxBufferDSPSize;
	}

	const float sample_y0 = mBuffer[index_y0];
	const float sample_y1 = mBuffer[index_y1];
	const float t = readPosition - (int)readPosition;

	double outSample = kap_linear_interp(sample_y0, sample_y1, t);

	return outSample;
}
