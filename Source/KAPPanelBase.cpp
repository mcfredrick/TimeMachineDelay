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

		const auto& glow_type = 0;
		const float w = getWidth();		//panel width
		const float h = getHeight();	//panel height
		const float t = 1.0f;			//line thickness

		switch (glow_type)
		{
			case(0): {

				//Add glow around panels when mouse over
				for (int i = 0; i < 4; i++) {

					g.setColour(KAPColour_glow.withAlpha(1.0f - ((float)i * 0.2f)));
					g.drawRoundedRectangle(i * t, i * t, getWidth() - 2 * i * t, getHeight() - 2 * i * t, 6.0 - i, t);
				}

			}break;


			case(1): {
			
				//Add a rainbow glow border around the active panel
				const Colour dColour[] = {
					Colours::red,
					Colours::orange,
					Colours::yellow,
					Colours::green,
					Colours::blue,
					Colours::purple
				};

				for (int i = 0; i < 6; i++) {

					g.setColour(dColour[i]);
					//g.setColour(Colour(256-10*i,256,256).withAlpha(0.1f*(float)i));
					g.drawRoundedRectangle(i * t, i * t, getWidth() - 2 * i * t, getHeight() - 2 * i * t, 6.0 - i, t);
				}

			}break;

		default:
			break;
		}

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