/*
  ==============================================================================

    parameterSlider.cpp
    Created: 22 Apr 2020 8:11:43pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "ParameterSlider.h"

ParameterSlider::ParameterSlider(AudioProcessorValueTreeState& stateToControl, const String& parameterID)
:   juce::Slider(parameterID)
{
    setSliderStyle(SliderStyle::LinearBarVertical);
    setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    setRange(0, 1);
    
    _attachment = std::make_unique<SliderAttachment>(stateToControl, parameterID, *this);
}
