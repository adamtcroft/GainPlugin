/*
  ==============================================================================

    nirRMS.cpp
    Created: 27 Jun 2020 11:43:22am
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "nirRMS.h"

nirRMS::nirRMS()
{
    _rmsValuesLeft = std::make_unique<std::deque<float>>();
    _rmsValuesRight = std::make_unique<std::deque<float>>();
    
    _rmsValuesLeft->resize(RMS_DEQUE_SIZE);
    _rmsValuesRight->resize(RMS_DEQUE_SIZE);
}

void nirRMS::process(int channelNumber, float rmsLevel)
{
    if(channelNumber == 0)
    {
        if(_rmsValuesLeft->size() == RMS_DEQUE_SIZE)
            _rmsValuesLeft->pop_front();
        _rmsValuesLeft->push_back(rmsLevel);
    }
    else if(channelNumber == 1)
    {
        if(_rmsValuesRight->size() == RMS_DEQUE_SIZE)
            _rmsValuesRight->pop_front();
        _rmsValuesRight->push_back(rmsLevel);
    }
    else
    {
        return;
    }
}
