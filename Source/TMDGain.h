/*
  ==============================================================================

    TMDGain.h
    Created: 3 Jul 2019 6:03:52pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

class TMDGain
{
public:

	TMDGain(); //constructor

	~TMDGain();	//destructor

	void process(float* inAudio,
				 float inGain,
				 float* outAudio,
				 int inNumSamplesToRender);

	float getMeterLevel();

private:

	float mOutputSmoothed;
};