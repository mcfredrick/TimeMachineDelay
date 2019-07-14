/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 4 Jul 2019 3:39:08pm
    Author:  Matt

  ==============================================================================
*/

#include "KAPPanelBase.h"
#include "KAPInterfaceDefines.h"

KAPPanelBase::KAPPanelBase(NewChorusFlangerAudioProcessor* inProcessor)
	:	mProcessor(inProcessor)
{

}

KAPPanelBase::~KAPPanelBase()
{

}

void KAPPanelBase::mouseEnter(const MouseEvent& event)
{
	repaint();
}

void KAPPanelBase::mouseExit(const MouseEvent& event)
{
	repaint();
}

void KAPPanelBase::paint(Graphics& g)
{
	//mouse over to change panel colors
	if (isMouseOver()) {

		const Colour hoverColour = Colour(Colours::black).withAlpha(0.4f);
		
		g.setColour(hoverColour);
		g.fillAll();
	}



	/*
	//An alternate paint routine for a solid color background with borders
	g.setColour(Colours::whitesmoke); //set the background color for the panel
	g.fillAll();

	g.setColour(Colours::black);
	g.drawRoundedRectangle(0, //x position
						   0, //y position
						   getWidth(), //width
						   getHeight(), //height
						   4, //corner size
						   2); //line thickness

	*/
}