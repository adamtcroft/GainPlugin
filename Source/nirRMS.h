/*
  ==============================================================================

    nirRMS.h
    Created: 27 Jun 2020 11:43:22am
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "HelperFunctions.h"
#include <numeric>

#define RMS_DEQUE_SIZE 100

class nirRMS
{
public:
    nirRMS();
    ~nirRMS() = default;
    
    void process(int channelNumber, float rmsLevel);
    
    inline float getRMSLevelInGain(int channelNumber)
    {
        if(channelNumber == 0 && _rmsValuesLeft->size() == RMS_DEQUE_SIZE)
            return std::accumulate(_rmsValuesLeft->begin(), _rmsValuesLeft->end(), 0.0f)/RMS_DEQUE_SIZE;
        else if(channelNumber == 1 && _rmsValuesRight->size() == RMS_DEQUE_SIZE)
            return std::accumulate(_rmsValuesRight->begin(), _rmsValuesRight->end(), 0.0f)/RMS_DEQUE_SIZE;
        else
            return 0.0f;
    };
    
    inline float getRMSLevelInDecibels(int channelNumber)
    {
            return Decibels::gainToDecibels(getRMSLevelInGain(channelNumber));
    };
    
private:
    std::unique_ptr<std::deque<float>> _rmsValuesLeft;
    std::unique_ptr<std::deque<float>> _rmsValuesRight;
};
