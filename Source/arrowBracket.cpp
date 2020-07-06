/*
  ==============================================================================

    arrowBracket.cpp
    Created: 5 Jul 2020 7:21:38pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "arrowBracket.h"

arrowBracket::arrowBracket()
:   _x(0),
    _flippedVertical(false),
    _flippedHorizontal(false)
{
    
}

void arrowBracket::paint(Graphics& g)
{
    g.setColour(Colours::cornsilk);
    
    if(_flippedVertical == true && _flippedHorizontal == false)
    {
        // Horizontal
        g.fillRect(45, _y + 10, 10, 2);
        
        // Vertical
        g.fillRect(45, _y, 2, 10);
    }
    else if(_flippedHorizontal == true && _flippedVertical == false)
    {
        //Horizontal
        g.fillRect(45, _y, 10, 2);
        
        //Vertical
        g.fillRect(55, _y, 2, 10);

    }
    else if(_flippedHorizontal == true && _flippedVertical == true)
    {
        DBG("both flipped");
        //Horizontal
        g.fillRect(45, _y + 10, 10, 2);
        
        //Vertical
        g.fillRect(53, _y, 2, 10);
    }
    else
    {
        //Horizontal
        g.fillRect(45, _y, 10, 2);
        
        //Vertical
        g.fillRect(45, _y, 2, 10);
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
