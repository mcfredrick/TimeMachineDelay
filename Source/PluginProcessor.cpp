/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TMDParameters.h"
#include "JuceHeader.h"

//==============================================================================
TimeMachineDelayAudioProcessor::TimeMachineDelayAudioProcessor()
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
					juce::Identifier("TMD"),	//valueTree identifier
					createParameterLayout()	)	//intialize parameters
#endif
{
	//initializeParameters(); //set up the parameter tree in the audio processor - overriden by createParameterLayout()
	initializeDSP(); //initialize DSP blocks
	mPresetManager = std::make_unique<TMDPresetManager>(this); //intitialize the preset manager passign a pointer to this audio processor
}

TimeMachineDelayAudioProcessor::~TimeMachineDelayAudioProcessor()
{
}

//==============================================================================
const String TimeMachineDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TimeMachineDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TimeMachineDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TimeMachineDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TimeMachineDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TimeMachineDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TimeMachineDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TimeMachineDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String TimeMachineDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void TimeMachineDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TimeMachineDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	for (int i = 0; i < 2; i++) {
		mDelay[i]->setSampleRate(sampleRate);
		mLFO[i]->setSampleRate(sampleRate);
	};
}

void TimeMachineDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

	for (int i = 0; i < 2; i++) {
		mDelay[i]->reset();
		mLFO[i]->reset();
	};
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TimeMachineDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TimeMachineDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

		float inputGain = *parameters.getRawParameterValue(TMDParameterID[kParameter_InputGain]);

		mInputGain[channel]->process(channelData,		 //inAudio
								inputGain,				 //gain parameter
								channelData,			 //outAudio
								buffer.getNumSamples()); //number of samples to render
		
		//turn delay into chorus by adding an LFO to one channel
		float rate = channel==0 ? *parameters.getRawParameterValue(TMDParameterID[kParameter_ModulationRate]): 0; //apply modulation to channel 0 (left) and set rate to 0 for channel 1 (right)

		float depth = *parameters.getRawParameterValue(TMDParameterID[kParameter_ModulationDepth]);

		mLFO[channel]->process(rate,					//rate
							   depth,					//depth
							   buffer.getNumSamples()); //number of samples to render

		float delayTime = *parameters.getRawParameterValue(TMDParameterID[kParameter_DelayTime]);
		float delayFeedback = *parameters.getRawParameterValue(TMDParameterID[kParameter_DelayFeedback]);
		float delayWetDry = *parameters.getRawParameterValue(TMDParameterID[kParameter_DelayWetDry]);
		float delayType = *parameters.getRawParameterValue(TMDParameterID[kParameter_DelayType]);

		mDelay[channel]->process(channelData,				 //inAudio
								 delayTime,					 //inTime
								 delayFeedback,				 //inFeedback
								 delayWetDry,				 //inWetDry
								 delayType,					 //inType
								 mLFO[channel]->getBuffer(), //modulation buffer
								 channelData,				 //outAudio
								 buffer.getNumSamples());	 //number of samples to render
		
		float outputGain = *parameters.getRawParameterValue(TMDParameterID[kParameter_OutputGain]);

		mOutputGain[channel]->process(channelData,			 //inAudio
								outputGain,					 //gain parameter
								channelData,				 //outAudio
								buffer.getNumSamples());	 //number of samples to render

    }
}

//==============================================================================
bool TimeMachineDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TimeMachineDelayAudioProcessor::createEditor()
{
    return new TimeMachineDelayAudioProcessorEditor (*this);
}

//==============================================================================
void TimeMachineDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	//this will be the parent element
	XmlElement preset("TMD_StateInfo");
	//this child elemnt goes inside and will store the parameters and values
	XmlElement* presetBody = new XmlElement("TMD_Preset");
	
	//populate the data in the preset body from the parameter state
	mPresetManager->getXmlForPreset(presetBody);

	//place the child element within the parent element with the values
	preset.addChildElement(presetBody);
	//convert the data to binary for storage
	copyXmlToBinary(preset, destData);
}

void TimeMachineDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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

float  TimeMachineDelayAudioProcessor::getInputGainMeterLevel(int inChannel)
{

	const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

float  TimeMachineDelayAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
	const float normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

void TimeMachineDelayAudioProcessor::initializeDSP()
{
	//iterate through each channel - currently set up for stereo 
	for (int i = 0; i < 2; i++) {

		//create new instances of each DSP object
		mInputGain[i] = std::make_unique<TMDGain>();
		mOutputGain[i] = std::make_unique <TMDGain>();
		mDelay[i] = std::make_unique <TMDDelay>();
		mLFO[i] = std::make_unique <TMDLFO>();
	};
}

/* 
//This method is overriden by createParameterLayout()

void TimeMachineDelayAudioProcessor::initializeParameters()
{	//add each of the needed parameters to the AudioProcessor
	for (int i = 0; i < kParameter_TotalNumParameters; i++) {
		parameters.createAndAddParameter(TMDParameterID[i],
			TMDParameterID[i],
			TMDParameterLabel[i],
			NormalisableRange<float>(0.0f, 1.0f),
			TMDParameterDefaultValue[i],
			nullptr,
			nullptr);

		//state must be initialized after all calls to createAndAddParameter()
		//creates a value tree with the parameter name given as the type
		//parameters.state = ValueTree(TMDParameterID[i]);
	};

	parameters.state = ValueTree(Identifier("TMD"));
}
*/

AudioProcessorValueTreeState::ParameterLayout TimeMachineDelayAudioProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<AudioParameterFloat>> params;

	for (int i = 0; i < kParameter_TotalNumParameters; i++) {

		params.push_back(std::make_unique<AudioParameterFloat>(TMDParameterID[i],
			TMDParameterLabel[i],
			NormalisableRange<float>(0.0f, 1.0f),
			TMDParameterDefaultValue[i]));
	}

	return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TimeMachineDelayAudioProcessor();
}
