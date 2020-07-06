/*
  ==============================================================================

    arrowBracket.h
    Created: 5 Jul 2020 7:21:38pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class arrowBracket : public Component, Timer
{
public:
    arrowBracket();
    ~arrowBracket() = default;
    
    void paint(Graphics& g) override;
    void timerCallback() override;
    void startTimer();
    void setY(int coordinate);
    void flipVertical();
    void flipHorizontal();
    
private:
    int _x, _y;
    bool _flippedVertical, _flippedHorizontal;
};
