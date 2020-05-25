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
    _avgVuSample = 0;
    
    _vuOutputBuffer.clear();
    
    for(int i=0; i < numberOfSamplesToRender; i++)
    {
        
        outputAudio[i] = inputAudio[i] * _smoother.getNextValue();
        _currentOutputValue = outputAudio[i];
        _vuOutputBuffer.push_back(outputAudio[i]);
    }
}

void nirGain::reset(double sampleRate)
{
    _smoother.reset(sampleRate, .4);
}

float nirGain::getValue()
{
    if(_vuOutputBuffer.size() > 0)
    {
        auto rms = std::sqrtf(std::abs(std::accumulate(_vuOutputBuffer.begin(), _vuOutputBuffer.end(), 0.0f)/_vuOutputBuffer.size()));
        DBG("RMS: " << rms);
        
        return rms;
    }
    else
        DBG("RETURNING ZERO");
        return 0.0f;
}
