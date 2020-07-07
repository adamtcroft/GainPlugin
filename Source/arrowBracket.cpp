/*
  ==============================================================================

    arrowBracket.cpp
    Created: 5 Jul 2020 7:21:38pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "arrowBracket.h"

arrowBracket::arrowBracket(int x, int y)
:   _x(x),
    _y(y),
    _flippedVertical(false),
    _flippedHorizontal(false)
{
    
}

void arrowBracket::paint(Graphics& g)
{
    g.setColour(Colours::lightgrey);
    
    if(_flippedVertical == true && _flippedHorizontal == false)
    {
        // Horizontal
        g.fillRect(_x, _y + 10, 10, 2);
        
        // Vertical
        g.fillRect(_x, _y, 2, 10);
    }
    else if(_flippedHorizontal == true && _flippedVertical == false)
    {
        //Horizontal
        g.fillRect(_x, _y, 10, 2);
        
        //Vertical
        g.fillRect(_x + 8, _y, 2, 10);

    }
    else if(_flippedHorizontal == true && _flippedVertical == true)
    {
        //Horizontal
        g.fillRect(_x, _y + 10, 10, 2);
        
        //Vertical
        g.fillRect(_x + 8, _y, 2, 10);
    }
    else
    {
        //Horizontal
        g.fillRect(_x, _y, 10, 2);
        
        //Vertical
        g.fillRect(_x, _y, 2, 10);
    }
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

void arrowBracket::flipVertical()
{
    _flippedVertical = true;
}

void arrowBracket::flipHorizontal()
{
    _flippedHorizontal = true;
}
