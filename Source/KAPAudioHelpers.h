/*
  ==============================================================================

    KAPAudioHelpers.h
    Created: 3 Jul 2019 6:02:57pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "JuceHeader.h"
#define kParameterSmoothingCoeff_Generic 0.04
#define kParameterSmoothingCoeff_Fine 0.002
#define kMeterSmoothingCoeff 0.2f

const static int maxBufferDSPSize = 192000; //max delay time * sample rate

const static double kPI = M_PI;
const static double k2PI = 2*M_PI;

static inline float dBToNormalizedGain(float inValue)
{
	//convert gain to decibels and apply a floor of 0.00001
	float inValuedB = Decibels::gainToDecibels(inValue + 0.00001f);
	//smooth the output
	inValuedB = (inValuedB + 96.0f) / 96.0f;

	return inValuedB;
}

//Linear Interpolation 
inline float kap_linear_interp(float v0, float v1, float t) 
{
	return (1 - t) * v0 + t * v1; //this one from wikipedia
}

//Rational tanh approximation for "soft-clipping"
inline double tanh_clip(double x)
{
	return x * (27 + x * x) / (27 + 9 * x * x); //from musicdsp.org
}

inline float kap_denormalize(float inValue)
{
	float absValue = fabs(inValue);

	if (absValue < 1e-15) {
		return 0.0f;
	} else {
		return inValue;
	}
}