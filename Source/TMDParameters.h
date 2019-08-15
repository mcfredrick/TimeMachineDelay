/*
  ==============================================================================

    TMDParameters.h
    Created: 5 Jul 2019 11:21:10am
    Author:  Matt

  ==============================================================================
*/

#pragma once

enum TMDParameter
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

static String TMDParameterID[kParameter_TotalNumParameters] =
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

static String TMDParameterLabel[kParameter_TotalNumParameters] =
{
	"Input Gain",
	"Time",
	"Feedback",
	"Wet Dry",
	"Type",
	"Output Gain",
	"Modulation Rate",
	"Modulation Depth",
};

static float TMDParameterDefaultValue[kParameter_TotalNumParameters] =
{
	0.5f, //Input Gain
	0.5f, //Time
	0.5f, //Feedback
	0.5f, //Wet Dry
	0.0f, //Type
	0.5f, //Output Gain
	0.5f, //Modulation Rate
	0.5f, //Modulation Depth
};