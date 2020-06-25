/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <numeric>
#include "nirGain.h"
#include "ParameterList.h"
#include "HelperFunctions.h"

//==============================================================================
/**
*/
class GainPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    GainPluginAudioProcessor();
    ~GainPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float getRMSLevelInGain();
    float getRMSLevelInDecibels();
    
    // Members
    AudioProcessorValueTreeState _parameters;
    float _rmsValue, _rmsLeft, _rmsRight, _peakValue, _peakLeft, _peakRight;
    
private:
    // Members
    std::unique_ptr<nirGain> _gain;
    std::deque<float> _rmsValues;
    
    // Functions
    void initializeDSP();
    AudioProcessorValueTreeState::ParameterLayout initializeParameters();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPluginAudioProcessor)
};
