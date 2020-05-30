/*
  ==============================================================================

    nirGain.cpp
    Created: 21 Apr 2020 9:29:00pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "nirGain.h"
#include <numeric>

void nirGain::process(float* inputAudio,
             float inputGain,
             float* outputAudio,
             int numberOfSamplesToRender)
{
    float gainMapped = jmap(inputGain, 0.0f, 1.0f, -55.0f, 12.0f);
    gainMapped = Decibels::decibelsToGain(gainMapped, -55.0f);
    
    _smoother.setTargetValue(gainMapped);
    
    for(int i=0; i < numberOfSamplesToRender; i++)
    {
        outputAudio[i] = inputAudio[i] * _smoother.getNextValue();
    }
}

void nirGain::reset(double sampleRate)
{
    _smoother.reset(sampleRate, .4);
}
