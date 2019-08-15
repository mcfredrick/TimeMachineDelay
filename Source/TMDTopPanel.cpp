/*
  ==============================================================================

    TMDTopPanel.cpp
    Created: 4 Jul 2019 3:41:06pm
    Author:  Matt

  ==============================================================================
*/

#include "TMDTopPanel.h"

TMDTopPanel::TMDTopPanel(TimeMachineDelayAudioProcessor* inProcessor)
	: TMDPanelBase(inProcessor)
{
	setSize(TOP_PANEL_WIDTH,
			TOP_PANEL_HEIGHT);

	int button_x = 15;
	int button_y = 10;
	int button_w = 55;
	int button_h = 25;

	mNewPreset = new TextButton();
	mNewPreset->setButtonText("NEW");
	mNewPreset->setBounds(button_x, button_y, button_w, button_h);
	mNewPreset->addListener(this);
	addAndMakeVisible(mNewPreset);
	button_x += button_w;

	mSavePreset = new TextButton();
	mSavePreset->setButtonText("SAVE");
	mSavePreset->setBounds(button_x, button_y, button_w, button_h);
	mSavePreset->addListener(this);
	addAndMakeVisible(mSavePreset);
	button_x += button_w;

	mSaveAsPreset = new TextButton();
	mSaveAsPreset->setButtonText("SAVE AS");
	mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
	mSaveAsPreset->addListener(this);
	addAndMakeVisible(mSaveAsPreset);
	button_x += button_w;

	const int comboBox_w = 200;
	const int comboBox_x = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;

	mPresetDisplay = new ComboBox();
	mPresetDisplay->setBounds(comboBox_w, button_y, comboBox_w, button_h);
	mPresetDisplay->addListener(this);
	addAndMakeVisible(mPresetDisplay);

	updatePresetComboBox();
}

TMDTopPanel::~TMDTopPanel()
{

}

void TMDTopPanel::paint(Graphics& g)
{
	TMDPanelBase::paint(g);

	g.setColour(TMDColour_1);
	g.setFont(font_2);

	const int label_w = 220;

	g.drawFittedText("Time Machine Delay", TOP_PANEL_WIDTH-label_w-10, 0, label_w, getHeight(), Justification::centredRight, 1);
}

void TMDTopPanel::buttonClicked(Button* b)
{
	TMDPresetManager* presetManager = mProcessor->getPresetManager();

	if (b == mNewPreset) {
		presetManager->createNewPreset();

		updatePresetComboBox();
	}

	else if (b == mSavePreset) {
		presetManager->savePreset();
	}

	else if (b == mSaveAsPreset) {
		displaySaveAsPopup();
	}
}

void TMDTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{

	

	if (comboBoxThatHasChanged == mPresetDisplay) {

		TMDPresetManager* presetManager = mProcessor->getPresetManager();

		const int index = mPresetDisplay->getSelectedItemIndex();
		presetManager->loadPreset(index);
	}

	
}

void TMDTopPanel::displaySaveAsPopup()
{
	TMDPresetManager* presetManager = mProcessor->getPresetManager();
	
	String currentPresetName = presetManager->getCurrentPresetName();

	AlertWindow window ("Save As", "Please enter a name for your preset", AlertWindow::NoIcon);

	window.centreAroundComponent(this, getWidth(), getHeight());
	window.addTextEditor("presetName", currentPresetName, "Preset name:");
	window.addButton("Confirm", 1);
	window.addButton("Cancel", 0);

	//takes the value returned by the confirm or cancel button
	//if the return wasn't 0 (cancel), save the preset as the name entered
	if (window.runModalLoop()) {

		String presetName = window.getTextEditor("presetName")->getText();
		presetManager->saveAsPreset(presetName);

		updatePresetComboBox();
	}

}

void TMDTopPanel::updatePresetComboBox()
{
	TMDPresetManager* presetManager = mProcessor->getPresetManager();
	String currentPresetName = presetManager->getCurrentPresetName();

	mPresetDisplay->clear(dontSendNotification);

	const int numPresets = presetManager->getNumberOfPresets();

	for (int i = 0; i < numPresets; i++) {
		mPresetDisplay->addItem(presetManager->getPresetName(i), (i + 1));
	}

	mPresetDisplay->setText(presetManager->getCurrentPresetName());
}