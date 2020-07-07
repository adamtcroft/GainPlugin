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

class rmsMeter : public Component, Timer
{
public:
    rmsMeter(GainPluginAudioProcessor* inputProcessor, int width, int height, int channelNumber);
    ~rmsMeter() = default;
    
    void paint(Graphics& g) override;
    void timerCallback() override;
    void startTimer();
    void setFillHeight(double height);
    int getMeterHeight();
    
private:
    GainPluginAudioProcessor* _processor;
    int _sliderWidth, _sliderHeight, _meterHeight, _channelNumber;
    double _sliderFillHeight;
    float _channelRMSLevel;
    Colour _meterColour;
};
