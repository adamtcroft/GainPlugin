/*
  ==============================================================================

    arrowBracket.cpp
    Created: 5 Jul 2020 7:21:38pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "arrowBracket.h"

arrowBracket::arrowBracket()
:   _x(0)
{
    
}

void arrowBracket::paint(Graphics& g)
{
    g.setColour(Colours::cornsilk);
    g.fillRect(45, _y, 10, 2);
    g.fillRect(45, _y, 2, 10);
}

void arrowBracket::timerCallback()
{
    repaint();
}

void arrowBracket::startTimer()
{
    startTimerHz(24);
}

void arrowBracket::setY(int coordinate)
{
    _y = coordinate;
}
