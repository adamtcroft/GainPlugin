/*
  ==============================================================================

    nirPeak.h
    Created: 14 Jul 2020 10:01:38am
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "HelperFunctions.h"

#define PEAK_DEQUE_SIZE 100

struct nirPeak
{
    nirPeak() = default;
    ~nirPeak() = default;
    
    void process(int channelNumber, float peakLevel);
    
    inline float getPeakLevelInGain(int channelNumber)
    {
        if(channelNumber == 0 && _peakValuesLeft.size() == PEAK_DEQUE_SIZE)
            return *std::max_element(_peakValuesLeft.begin(), _peakValuesLeft.end());
        else if(channelNumber == 1 && _peakValuesRight.size() == PEAK_DEQUE_SIZE)
            return *std::max_element(_peakValuesRight.begin(), _peakValuesRight.end());
        else
            return 0.f;
    }
    
    inline float getPeakLevelInDecibels(int channelNumber)
    {
        return Decibels::gainToDecibels(getPeakLevelInGain(channelNumber));
    }
    
private:
    std::deque<float> _peakValuesLeft, _peakValuesRight;
};
