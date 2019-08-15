/*
  ==============================================================================

    TMDLookAndFeel.h
    Created: 10 Jul 2019 3:24:43pm
    Author:  mcfre

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "TMDInterfaceDefines.h"

class TMDLookAndFeel
	: public LookAndFeel_V4
{
public:

	TMDLookAndFeel()
	{

		//image assets
		mSliderImage = ImageCache::getFromMemory(BinaryData::kadenze_knob_png, BinaryData::kadenze_knob_pngSize);
		
		//comboBox colours
		setColour(ComboBox::backgroundColourId, TMDColour_3);
		setColour(ComboBox::outlineColourId, TMDColour_2);
		setColour(ComboBox::arrowColourId, TMDColour_1);
		setColour(ComboBox::textColourId, TMDColour_1);

		//button colours
		setColour(TextButton::buttonColourId, TMDColour_1);
		setColour(TextButton::textColourOnId, TMDColour_1);
		setColour(TextButton::textColourOffId, TMDColour_1);
	}
	~TMDLookAndFeel()
	{

	}

	/*Buttons*/

	Font getTextButtonFont(TextButton&, int buttonHeight) override
	{
		return font_1;
	}

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
							  bool isMouseOverButton, bool isButtonDown) override
	{
		Colour fillColour;

		if (isButtonDown) {
			fillColour = TMDColour_6;
		} else if (isMouseOverButton) {
			fillColour = TMDColour_3;
		} else {
			fillColour = TMDColour_5;
		}

		const float cornerSize = 6.0f;
		const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
		
		g.setColour(fillColour);
		g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
	}

	/*Combo Boxes*/

	Font getLabelFont(Label& Label) override
	{
		return font_1;
	}

	void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
						   bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
						   const String& text, const String& shortcutKeyText,
						   const Drawable* icon, const Colour* textColour) override
	{
		juce::Rectangle<int> r(area);

		Colour fillColour = (isHighlighted) ? TMDColour_5 : TMDColour_4;
	
		g.setColour(fillColour);
		g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);
	
		Colour myTextColour = isTicked ? TMDColour_7 : TMDColour_1;
		g.setColour(myTextColour);
		g.setFont(font_1);
		
		r.setLeft(10);
		r.setY(1);
		g.drawFittedText(text, r, Justification::left, 1);
	}

	void drawComboBox(Graphics& g, int width, int height, bool,
					  int, int, int, int,
					  ComboBox& box) override
	{
		const float cornerSize = 3.0f;
		const juce::Rectangle<int> boxBounds(0, 0, width, height);

		g.setColour(TMDColour_3);
		g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);
		
		juce::Rectangle<int> arrow(width - 30, 0, 20, height);

		Path path;

		path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
		path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
		path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);

		Colour arrowColour = box.findColour(ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
		g.setColour(arrowColour);
		g.strokePath(path, PathStrokeType(2.0f));
	}
	
	/*Sliders*/

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, 
						  float sliderPos, const float rotaryStartAngle, 
						  const float rotaryEndAngle, Slider& slider) override
	{
		//divide the knob slider image strip into square frames
		const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
		//relate the image strip to the slider position from the editor
		const int frameIndex = (int)std::ceil(sliderPos * (numFrames-1));
	
		const float radius = jmin(width * 0.5, height * 0.5);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;

		g.drawImage(mSliderImage, //image
					rx,				//destination x
					ry,				//destination y
					2 * radius,		//destination width
					2 * radius,		//destination height
					0,				//source x
					frameIndex * mSliderImage.getWidth(), //source y
					mSliderImage.getWidth(), //source width
					mSliderImage.getWidth()); //source height
	}


private:

	Image mSliderImage;

};