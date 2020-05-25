/*
  ==============================================================================

    vuMeter.cpp
    Created: 11 May 2020 6:26:54pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "vuMeter.h"
#define meterSmoothingCoefficient .96

vuMeter::vuMeter(GainPluginAudioProcessor* inputProcessor, int width, int height)
:   _processor(inputProcessor),
    _parameterID(-1),
    _paintCount(0),
    _sliderWidth(width),
    _sliderHeight(height),
    _channelLevel(0.0f)
{
}

void vuMeter::paint(Graphics& g)
{
    int channelFill = getHeight() - (getHeight() * _channelLevel);
    
    if(_channelLevel <= 0)
    {
        channelFill = 250;
        _channelLevel = 0;
    }
    
    int newRange = jmap(_fillHeight, 250.0, 0.0);
    int newFill = jmap(channelFill, 250, 0, 250, newRange);
    
    g.setColour(Colours::crimson);
    g.fillRect(0, newFill, getWidth(), getHeight()+20);
        
    repaint();
}

void vuMeter::timerCallback()
{
    float updatedChannelLevel = _processor->getChannelLevel(0);

    if(updatedChannelLevel > _channelLevel)
        _channelLevel = updatedChannelLevel;
    else
        _channelLevel = meterSmoothingCoefficient * (_channelLevel - updatedChannelLevel) + updatedChannelLevel;

    _channelLevel = denormalize(_channelLevel);
}

void vuMeter::setParameterID(int inputParameterID)
{
    _parameterID = inputParameterID;
    startTimerHz(15);
}

void vuMeter::setFillHeight(double height)
{
    _fillHeight = height;
}

void vuMeter::setMeterColour(Colour colour)
{
    _meterColour = colour;
}
