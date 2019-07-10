/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 4 Jul 2019 3:39:08pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPPanelBase.h"

KAPPanelBase::KAPPanelBase(NewChorusFlangerAudioProcessor* inProcessor)
	:	mProcessor(inProcessor)
{

}

KAPPanelBase::~KAPPanelBase()
{

}

void KAPPanelBase::paint(Graphics& g)
{
	g.setColour(Colours::lightskyblue); //set the background color for the panel
	g.fillAll();

	g.setColour(Colours::black);
	g.drawRoundedRectangle(0, //x position
						   0, //y position
						   getWidth(), //width
						   getHeight(), //height
						   4, //corner size
						   2); //line thickness
}