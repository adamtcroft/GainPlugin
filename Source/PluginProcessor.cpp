/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define RMS_DEQUE_SIZE 100
#define PEAK_DEQUE_SIZE 100

using parametersVector = std::vector<std::unique_ptr<AudioProcessorValueTreeState::Parameter>>;
using apvtsParameter = AudioProcessorValueTreeState::Parameter;

//==============================================================================
GainPluginAudioProcessor::GainPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        _parameters(*this, nullptr, "Parameters", initializeParameters())
#endif
{
    initializeDSP();
}

GainPluginAudioProcessor::~GainPluginAudioProcessor()
{
}

//==============================================================================
const String GainPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String GainPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    _gain->reset(sampleRate);
}

void GainPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void GainPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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
        
        auto gainValue = _parameters.getParameterAsValue(parameterIDs[Parameter_Gain]).getValue();
        
        _gain->process(channelData, gainValue, channelData, buffer.getNumSamples());
        
        if(channel == 0)
        {
            if(_peakValuesLeft.size() == PEAK_DEQUE_SIZE)
                _peakValuesLeft.pop_front();
            _peakValuesLeft.push_back(buffer.getMagnitude(0, 0, buffer.getNumSamples()));
            
            if(_rmsValuesLeft.size() == RMS_DEQUE_SIZE)
                _rmsValuesLeft.pop_front();
            _rmsValuesLeft.push_back(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        }
        else
        {
            if(_peakValuesRight.size() == PEAK_DEQUE_SIZE)
                _peakValuesRight.pop_front();
            _peakValuesRight.push_back(buffer.getMagnitude(1, 0, buffer.getNumSamples()));
            
            if(_rmsValuesRight.size() == RMS_DEQUE_SIZE)
                _rmsValuesRight.pop_front();
            _rmsValuesRight.push_back(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
        }
    }
}

//==============================================================================
bool GainPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainPluginAudioProcessor::createEditor()
{
    return new GainPluginAudioProcessorEditor (*this);
}

//==============================================================================
void GainPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainPluginAudioProcessor();
}

void GainPluginAudioProcessor::initializeDSP()
{
    _gain = std::make_unique<nirGain>();
}

AudioProcessorValueTreeState::ParameterLayout GainPluginAudioProcessor::initializeParameters()
{
    parametersVector parametersVector;
    float initialValue = jmap(0.5, -55.0, 12.0, 0.0, 1.0);
    
    for(int i = 0; i < TotalNumParameters; i++)
    {
        std::unique_ptr<apvtsParameter> parameter =
        std::make_unique<apvtsParameter>(parameterIDs[i],
                                         parameterNames[i],
                                         parameterNames[i],
                                         NormalisableRange<float>(0.0f, 1.0f),
                                         initialValue,
                                         nullptr,
                                         nullptr);
        parametersVector.push_back(std::move(parameter));
    }
    
    return{parametersVector.begin(), parametersVector.end()};
}

// I'll need one of these for left and one for right
// or I can just return an object with both values
float GainPluginAudioProcessor::getRMSLevelInGain(int channelNumber)
{
    if(channelNumber == 0 && _rmsValuesLeft.size() == RMS_DEQUE_SIZE)
        return std::accumulate(_rmsValuesLeft.begin(), _rmsValuesLeft.end(), 0.0f)/RMS_DEQUE_SIZE;
    else if(channelNumber == 1 && _rmsValuesRight.size() == RMS_DEQUE_SIZE)
        return std::accumulate(_rmsValuesRight.begin(), _rmsValuesRight.end(), 0.0f)/RMS_DEQUE_SIZE;
    else
        return 0.0f;
}

// I'll need one of these for left and one for right
// or I can just return an object with both values
float GainPluginAudioProcessor::getRMSLevelInDecibels(int channelNumber)
{
    return Decibels::gainToDecibels(getRMSLevelInGain(channelNumber));
}

// I'll need one of these for left and one for right
// or I can just return an object with both values
float GainPluginAudioProcessor::getPeakLevelInGain(int channelNumber)
{
    if(channelNumber == 0 && _peakValuesLeft.size() == PEAK_DEQUE_SIZE)
        return *std::max_element(_peakValuesLeft.begin(), _peakValuesLeft.end());
    else if(channelNumber == 1 && _peakValuesRight.size() == PEAK_DEQUE_SIZE)
        return *std::max_element(_peakValuesRight.begin(), _peakValuesRight.end());
    else
        return 0.f;
}

// I'll need one of these for left and one for right
// or I can just return an object with both values
float GainPluginAudioProcessor::getPeakLevelInDecibels(int channelNumber)
{
    return Decibels::gainToDecibels(getPeakLevelInGain(channelNumber));
}
