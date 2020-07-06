/*
  ==============================================================================

    vuMeter.cpp
    Created: 11 May 2020 6:26:54pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "rmsMeter.h"
#define meterSmoothingCoefficient .6
#define panMakeup 2.8

rmsMeter::rmsMeter(GainPluginAudioProcessor* inputProcessor, int width, int height, int channelNumber)
:   _processor(inputProcessor),
    _sliderWidth(width),
    _sliderHeight(height),
    _vuMeterHeight(0),
    _channelNumber(channelNumber),
    _channelRMSLevel(0.0f)
{
}

void rmsMeter::paint(Graphics& g)
{
    // Set VU meter empty if there is no signal
    if(_channelRMSLevel <= 0 || isinf(_channelRMSLevel))
    {
        _channelRMSLevel = 0;
    }
    
    float decibelValue = Decibels::gainToDecibels(_channelRMSLevel);
    int topOfSlider = jmap(_sliderFillHeight, 250.0, 0.0);
    
    _vuMeterHeight = jmap(decibelValue,
                          -100.f,
                          0.f,
                          static_cast<float>(SLIDER_HEIGHT),
                          static_cast<float>(topOfSlider));
    
    g.setColour(Colours::crimson);
    g.fillRect(0, _vuMeterHeight, getWidth(), getHeight()+20);
}

void rmsMeter::timerCallback()
{
    float updatedChannelLevel = _processor->getRMSLevelInGain(_channelNumber);

    if(updatedChannelLevel >= _channelRMSLevel)
        _channelRMSLevel = updatedChannelLevel;
    else
        _channelRMSLevel = meterSmoothingCoefficient * (_channelRMSLevel - updatedChannelLevel) + updatedChannelLevel;
    
    repaint();
}

void rmsMeter::startTimer()
{
    startTimerHz(24);
}

void rmsMeter::setFillHeight(double height)
{
    _sliderFillHeight = height;
}

int rmsMeter::getMeterHeight()
{
    return _vuMeterHeight;
}
