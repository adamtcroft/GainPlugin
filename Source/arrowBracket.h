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
    arrowBracket(int x, int y);
    ~arrowBracket() = default;
    
    void paint(Graphics& g) override;
    void timerCallback() override;
    
    inline void startTimer() { startTimerHz(24); };
    inline void setY(int coordinate) {  _y = coordinate; };
    inline void flipVertical() { _flippedVertical = true; };
    inline void flipHorizontal() { _flippedHorizontal = true; };
    
private:
    int _x, _y;
    bool _flippedVertical, _flippedHorizontal;
};
