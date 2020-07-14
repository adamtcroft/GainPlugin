/*
  ==============================================================================

    nirPeak.cpp
    Created: 14 Jul 2020 10:01:38am
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "nirPeak.h"

void nirPeak::process(int channelNumber, float peakLevel)
{
    if(channelNumber == 0)
    {
        if(_peakValuesLeft.size() == PEAK_DEQUE_SIZE)
            _peakValuesLeft.pop_front();
        _peakValuesLeft.push_back(peakLevel);
    }
    else if(channelNumber == 1)
    {
        if(_peakValuesRight.size() == PEAK_DEQUE_SIZE)
            _peakValuesRight.pop_front();
        _peakValuesRight.push_back(peakLevel);
    }
    else
    {
        return;
    }
}
