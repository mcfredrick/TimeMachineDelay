/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "KAPParameters.h"
#include "JuceHeader.h"

//==============================================================================
NewChorusFlangerAudioProcessor::NewChorusFlangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
		parameters(*this,						//reference to processor
					nullptr,					//nullptr to undoManager (optional)
					juce::Identifier("KAP"),	//valueTree identifier
					createParameterLayout()	)	//intialize parameters
#endif
{
	//initializeParameters(); //set up the parameter tree in the audio processor - overriden by createParameterLayout()
	initializeDSP(); //initialize DSP blocks
	mPresetManager = std::make_unique<KAPPresetManager>(this); //intitialize the preset manager passign a pointer to this audio processor
}

NewChorusFlangerAudioProcessor::~NewChorusFlangerAudioProcessor()
{
}

//==============================================================================
const String NewChorusFlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewChorusFlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewChorusFlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewChorusFlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewChorusFlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewChorusFlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewChorusFlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewChorusFlangerAudioProcessor::setCurrentProgram (int index)
{
}

const String NewChorusFlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewChorusFlangerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewChorusFlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	for (int i = 0; i < 2; i++) {
		mDelay[i]->setSampleRate(sampleRate);
		mLFO[i]->setSampleRate(sampleRate);
	};
}

void NewChorusFlangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

	for (int i = 0; i < 2; i++) {
		mDelay[i]->reset();
		mLFO[i]->reset();
	};
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewChorusFlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewChorusFlangerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...

		float inputGain = *parameters.getRawParameterValue(KAPParameterID[kParameter_InputGain]);

		mInputGain[channel]->process(channelData,		 //inAudio
								inputGain,				 //gain parameter
								channelData,			 //outAudio
								buffer.getNumSamples()); //number of samples to render
		
		//turn delay into chorus by adding an LFO to one channel
		float rate = channel==0 ? *parameters.getRawParameterValue(KAPParameterID[kParameter_ModulationRate]): 0; //apply modulation to channel 0 (left) and set rate to 0 for channel 1 (right)

		float depth = *parameters.getRawParameterValue(KAPParameterID[kParameter_ModulationDepth]);

		mLFO[channel]->process(rate,					//rate
							   depth,					//depth
							   buffer.getNumSamples()); //number of samples to render

		float delayTime = *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayTime]);
		float delayFeedback = *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayFeedback]);
		float delayWetDry = *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayWetDry]);
		float delayType = *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayType]);

		mDelay[channel]->process(channelData,				 //inAudio
								 delayTime,					 //inTime
								 delayFeedback,				 //inFeedback
								 delayWetDry,				 //inWetDry
								 delayType,					 //inType
								 mLFO[channel]->getBuffer(), //modulation buffer
								 channelData,				 //outAudio
								 buffer.getNumSamples());	 //number of samples to render
		
		float outputGain = *parameters.getRawParameterValue(KAPParameterID[kParameter_OutputGain]);

		mOutputGain[channel]->process(channelData,			 //inAudio
								outputGain,					 //gain parameter
								channelData,				 //outAudio
								buffer.getNumSamples());	 //number of samples to render

    }
}

//==============================================================================
bool NewChorusFlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewChorusFlangerAudioProcessor::createEditor()
{
    return new NewChorusFlangerAudioProcessorEditor (*this);
}

//==============================================================================
void NewChorusFlangerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	//this will be the parent element
	XmlElement preset("KAP_StateInfo");
	//this child elemnt goes inside and will store the parameters and values
	XmlElement* presetBody = new XmlElement("KAP_Preset");
	
	//populate the data in the preset body from the parameter state
	mPresetManager->getXmlForPreset(presetBody);

	//place the child element within the parent element with the values
	preset.addChildElement(presetBody);
	//convert the data to binary for storage
	copyXmlToBinary(preset, destData);
}

void NewChorusFlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	
	std::unique_ptr<XmlElement> xmlState;
	//create an XML Element from the raw data passed
	//xmlState.reset(getXmlFromBinary(data, sizeInBytes));
	xmlState = getXmlFromBinary(data, sizeInBytes);

	//make sure the xmlState is not a nullptr and stop if it doesn't exist
	if (xmlState) {
		//iterate through the data and pass the elements to the preset mangager load function
		forEachXmlChildElement(*xmlState, subChild) {
			mPresetManager->loadPresetForXml(subChild);
		};
	}
	else {
		jassertfalse;
	}
}

float  NewChorusFlangerAudioProcessor::getInputGainMeterLevel(int inChannel)
{

	const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

float  NewChorusFlangerAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
	const float normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

void NewChorusFlangerAudioProcessor::initializeDSP()
{
	//iterate through each channel - currently set up for stereo 
	for (int i = 0; i < 2; i++) {

		//create new instances of each DSP object
		mInputGain[i] = std::make_unique<KAPGain>();
		mOutputGain[i] = std::make_unique <KAPGain>();
		mDelay[i] = std::make_unique <KAPDelay>();
		mLFO[i] = std::make_unique <KAPLFO>();
	};
}

/* 
//This method is overriden by createParameterLayout()

void NewChorusFlangerAudioProcessor::initializeParameters()
{	//add each of the needed parameters to the AudioProcessor
	for (int i = 0; i < kParameter_TotalNumParameters; i++) {
		parameters.createAndAddParameter(KAPParameterID[i],
			KAPParameterID[i],
			KAPParameterLabel[i],
			NormalisableRange<float>(0.0f, 1.0f),
			KAPParameterDefaultValue[i],
			nullptr,
			nullptr);

		//state must be initialized after all calls to createAndAddParameter()
		//creates a value tree with the parameter name given as the type
		//parameters.state = ValueTree(KAPParameterID[i]);
	};

	parameters.state = ValueTree(Identifier("KAP"));
}
*/

AudioProcessorValueTreeState::ParameterLayout NewChorusFlangerAudioProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<AudioParameterFloat>> params;

	for (int i = 0; i < kParameter_TotalNumParameters; i++) {

		params.push_back(std::make_unique<AudioParameterFloat>(KAPParameterID[i],
			KAPParameterLabel[i],
			NormalisableRange<float>(0.0f, 1.0f),
			KAPParameterDefaultValue[i]));
	}

	return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewChorusFlangerAudioProcessor();
}
