/*
  ==============================================================================

    KAPParameters.h
    Created: 5 Jul 2019 11:21:10am
    Author:  Matt

  ==============================================================================
*/

#pragma once

enum KAPParameter
{
	kParameter_InputGain = 0,
	kParameter_DelayTime,
	kParameter_DelayFeedback,
	kParameter_DelayWetDry,
	kParameter_DelayType,
	kParameter_OutputGain,
	kParameter_ModulationRate,
	kParameter_ModulationDepth,
	kParameter_TotalNumParameters,
};

static String KAPParameterID[kParameter_TotalNumParameters] =
{
	"InputGain",
	"Time",
	"Feedback",
	"WetDry",
	"Type",
	"OutputGain",
	"ModulationRate",
	"ModulationDepth",
};