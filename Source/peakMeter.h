/*
  ==============================================================================

    peakMeter.h
    Created: 24 Jun 2020 6:42:35pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class peakMeter : public Component, Timer
{
public:
    peakMeter(GainPluginAudioProcessor* inputProcessor, int width, int height, int channelNumber);
    ~peakMeter() = default;
    
    void paint(Graphics& g) override;
    void timerCallback() override;
    
    inline void startTimer() { startTimerHz(24); };
    inline void setFillHeight(double height) { _sliderFillHeight = height; };
    inline int getMeterHeight() { return _meterHeight; };
    
private:
    GainPluginAudioProcessor* _processor;
    int _sliderWidth, _sliderHeight, _channelNumber, _meterHeight;
    float _channelPeakLevel;
    double _sliderFillHeight;
};
