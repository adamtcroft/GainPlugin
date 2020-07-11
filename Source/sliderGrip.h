/*
  ==============================================================================

    sliderGrip.h
    Created: 13 May 2020 7:41:17pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"

class sliderGrip : public Component
{
public:
    sliderGrip(GainPluginAudioProcessor* inputProcessor);
    ~sliderGrip() = default;
    
    void paint(Graphics& g) override;
    inline void setValue(float&& value) { _sliderValue = value; };
    inline void setGripColour(Colour colour) { _gripColour = colour; };
    
private:
    GainPluginAudioProcessor* _processor;
    float _sliderValue;
    Colour _gripColour;
};
