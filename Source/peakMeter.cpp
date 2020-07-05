/*
  ==============================================================================

    peakMeter.cpp
    Created: 24 Jun 2020 6:42:35pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "peakMeter.h"
#define meterSmoothingCoefficient .6

peakMeter::peakMeter(GainPluginAudioProcessor* inputProcessor, int width, int height, int channelNumber)
:   _processor(inputProcessor),
    _sliderWidth(width),
    _sliderHeight(height),
    _channelNumber(channelNumber),
    _channelPeakLevel(0.0f)
{
    
}

void peakMeter::paint(Graphics& g)
{
    int topOfSlider = jmap(_sliderFillHeight, 250.0, 0.0);
    
    float peakDecibelValue = _processor->getPeakLevelInDecibels(_channelNumber);
    int peakMeterHeight = jmap(peakDecibelValue,
                               -100.f,
                               0.f,
                               static_cast<float>(SLIDER_HEIGHT),
                               static_cast<float>(topOfSlider));
    
    DBG("Slider top: " << topOfSlider);
    DBG("Peak Meter Height: " << peakMeterHeight);
    
    
    g.setColour(Colours::lightseagreen);
    g.fillRect(0, peakMeterHeight, getWidth(), 5);
}

void peakMeter::timerCallback()
{
    // Set VU meter empty if there is no signal
    if(_channelPeakLevel <= 0 || isinf(_channelPeakLevel))
    {
        _channelPeakLevel = 0;
    }
    
    float updatedPeakLevel = _processor->getPeakLevelInGain(_channelNumber);
    
    if(updatedPeakLevel >= _channelPeakLevel)
        _channelPeakLevel = updatedPeakLevel;
    else
        _channelPeakLevel = meterSmoothingCoefficient * (_channelPeakLevel - updatedPeakLevel) + updatedPeakLevel;
    
    repaint();
}

void peakMeter::startTimer()
{
    startTimerHz(24);
}

void peakMeter::setFillHeight(double height)
{
    _sliderFillHeight = height;
}
