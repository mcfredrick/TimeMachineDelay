/*
  ==============================================================================

    KAPPresetManager.h
    Created: 9 Jul 2019 4:08:04pm
    Author:  mcfre

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".kpf"

class KAPPresetManager
{
	public: 

		KAPPresetManager(AudioProcessor* inProcessor);
		~KAPPresetManager();

		void getXmlForPreset(XmlElement* inElement);

		void loadPresetForXml(XmlElement* inElement);

		int getNumberOfPresets();

		String getPresetName(int inPresetIndex);

		void createNewPreset();

		void savePreset();

		void saveAsPreset(String inPresetName);

		void loadPreset(int inPresetName);

		bool getIsCurrentPresetSaved();

		String getCurrentPresetName();

	private:

		//store all presets in memory in the preset manager
		void storeLocalPreset();

		bool mCurrentPresetIsSaved;

		File mCurrentlyLoadedPreset;

		Array<File> mLocalPresets;

		String mCurrentPresetName;

		String mPresetDirectory;

		XmlElement* mCurrentPresetXml;
		//pointer to an audio processor member variable
		AudioProcessor* mProcessor;
};