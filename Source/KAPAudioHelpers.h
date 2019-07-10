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

#define kParameterSmoothingCoeff_Generic 0.04
#define kParameterSmoothingCoeff_Fine 0.002

const static int maxBufferDSPSize = 192000; //max delay time * sample rate

const static double kPI = M_PI;
const static double k2PI = 2*M_PI;

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