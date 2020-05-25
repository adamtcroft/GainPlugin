/*
  ==============================================================================

    HelperFunctions.h
    Created: 28 Apr 2020 11:13:03pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "GlobalDefines.h"

inline void paintComponentLabel(Graphics& g, Component* inComponent, float uiWidth)
{
    const int y = inComponent->getY() + (inComponent->getHeight() + 5);
    const int width = inComponent->getWidth() * .7;
//    const int x = inComponent->getX() + (width * .25);
    const int x = (uiWidth * 0.5) - (width * 0.5);
    const int height = 20;
    const float cornerSize = 3.0f;
    
    const String label = inComponent->getName();
    
    g.setColour(Colours::darkgrey);
    g.fillRoundedRectangle(x, y, width, height, cornerSize);
    
    g.setColour(Colours::white);
    g.setFont(labelFont);

    g.drawFittedText(label, x, y, width, height, Justification::centred, 1);
}

static inline float dBToNormalizedGain(float inValue)
{
    float inValueindB = Decibels::gainToDecibels(inValue + 0.00001f);
    inValueindB = (inValueindB + 96.f) / 96.f;
    
    return inValueindB;
}

inline float denormalize(float inValue)
{
    float absValue = fabs(inValue);
    
    if(absValue < 1e-15)
        return 0.0f;
    else
        return inValue;
}
