/*
  ==============================================================================

    KAPGain.cpp
    Created: 3 Jul 2019 6:03:52pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPGain.h"

#include "JuceHEader.h"

	KAPGain::KAPGain() //constructor
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
	}