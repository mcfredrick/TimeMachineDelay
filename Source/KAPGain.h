/*
  ==============================================================================

    KAPGain.h
    Created: 3 Jul 2019 6:03:52pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

class KAPGain
{
public:

	KAPGain(); //constructor

	~KAPGain();	//destructor

	void process(float* inAudio,
				 float inGain,
				 float* outAudio,
				 int inNumSamplesToRender);

	float getMeterLevel();

private:

	float mOutputSmoothed;
};