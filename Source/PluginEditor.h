/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ParameterSlider.h"
#include "GlobalDefines.h"
#include "MainPanel.h"

//==============================================================================
/**
*/
class GainPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GainPluginAudioProcessorEditor (GainPluginAudioProcessor&);
    ~GainPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainPluginAudioProcessor& processor;
    std::unique_ptr<MainPanel> _mainPanel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPluginAudioProcessorEditor)
};
