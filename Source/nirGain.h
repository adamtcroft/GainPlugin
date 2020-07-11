/*
  ==============================================================================

    nirGain.h
    Created: 21 Apr 2020 9:29:00pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "HelperFunctions.h"

class nirGain
{
public:
    nirGain() = default;
    ~nirGain() = default;
    
    void process(float* inputAudio,
                 float inputGain,
                 float* outputAudio,
                 int numberOfSamplesToRender);
    
    void reset(double sampleRate);

private:
    SmoothedValue<float, ValueSmoothingTypes::Linear> _smoother;
};
