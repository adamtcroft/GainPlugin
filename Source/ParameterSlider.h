/*
  ==============================================================================

    parameterSlider.h
    Created: 22 Apr 2020 8:11:43pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using SliderAttachment = AudioProcessorValueTreeState::SliderAttachment;

class ParameterSlider : public Slider
{
public:
    ParameterSlider(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
    ~ParameterSlider() = default;
    
private:
    std::unique_ptr<SliderAttachment> _attachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider);
};
