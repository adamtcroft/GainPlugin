/*
  ==============================================================================

    vuMeter.h
    Created: 11 May 2020 6:26:54pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "HelperFunctions.h"
#include <string>

class vuMeter : public Component, Timer
{
public:
    vuMeter(GainPluginAudioProcessor* inputProcessor, int width, int height);
    ~vuMeter() = default;
    
    void paint(Graphics& g) override;
    void timerCallback() override;
    void setParameterID(int inputParameterID);
    void setFillHeight(double height);
    void setMeterColour(Colour colour);
    
private:
    GainPluginAudioProcessor* _processor;
    int _parameterID, _paintCount, _sliderWidth, _sliderHeight;
    double _fillHeight;
    float _channelLevel;
    Colour _meterColour;
};
