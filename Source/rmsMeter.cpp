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

rmsMeter::rmsMeter(GainPluginAudioProcessor* inputProcessor, int width, int height)
:   _processor(inputProcessor),
    _parameterID(-1),
    _paintCount(0),
    _sliderWidth(width),
    _sliderHeight(height),
    _vuMeterHeight(0),
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
    
//    float peakDecibelValue = _processor->getPeakLevelInDecibels();
//    int peakMeterHeight = jmap(peakDecibelValue,
//                               -100.f,
//                               0.f,
//                               static_cast<float>(SLIDER_HEIGHT),
//                               static_cast<float>(topOfSlider));
    
    
//    g.setColour(Colours::lightseagreen);
//    g.fillRect(0, peakMeterHeight, getWidth(), 5);
    
    g.setColour(Colours::crimson);
    g.fillRect(0, _vuMeterHeight, getWidth(), getHeight()+20);
}

void rmsMeter::timerCallback()
{
    float updatedChannelLevel = _processor->getRMSLevelInGain();
//    float updatedPeakLevel = _processor->getPeakLevelInGain();

    if(updatedChannelLevel >= _channelRMSLevel)
        _channelRMSLevel = updatedChannelLevel;
    else
        _channelRMSLevel = meterSmoothingCoefficient * (_channelRMSLevel - updatedChannelLevel) + updatedChannelLevel;
    
//    if(updatedPeakLevel >= _channelPeakLevel)
//        _channelPeakLevel = updatedPeakLevel;
//    else
//        _channelPeakLevel = meterSmoothingCoefficient * (_channelPeakLevel - updatedPeakLevel) + updatedPeakLevel;
    
    repaint();
}

void rmsMeter::setParameterID(int inputParameterID)
{
    _parameterID = inputParameterID;
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
