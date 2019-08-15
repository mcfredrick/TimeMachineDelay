/*
  ==============================================================================

    TMDHelperFunctions.h
    Created: 7 Jul 2019 11:20:54pm
    Author:  mcfre

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "TMDInterfaceDefines.h"

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
	const int x = inComponent->getX() - inComponent->getWidth() * 0.25f;
	const int y = inComponent->getY() + inComponent->getHeight();
	const int w = inComponent->getWidth() * 1.5f;
	const int h = 20;
	const float cornerSize = 3.0f;

	const String label = inComponent->getName();
	const float cornersize = 3.0f;

	g.setColour(TMDColour_3);
	g.fillRoundedRectangle(x, y, w, h, cornerSize);

	g.setColour(TMDColour_1);
	g.setFont(font_1);

	g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}