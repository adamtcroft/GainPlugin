/*
  ==============================================================================

    signalLabel.cpp
    Created: 5 Jul 2020 6:02:01pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "signalLabel.h"

signalLabel::signalLabel(int x, int y, bool flip)
:   _x(x),
    _y(y),
    _topArrowHeight(0),
    _fadedIn(false)
{
    _topArrow = std::make_unique<arrowBracket>(_x, _y);
    _topArrow->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _topArrow->startTimer();
    if(flip == true)
    {
        _topArrow->flipHorizontal();
        _x += 3;
    }
    else
        _x -= 4;
    addAndMakeVisible(*_topArrow);
    
    _bottomArrow = std::make_unique<arrowBracket>(_x, _y);
    _bottomArrow->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _bottomArrow->startTimer();
    _bottomArrow->flipVertical();
    if(flip == true)
    {
        _bottomArrow->flipHorizontal();
        _x += 3;
    }
    else
        _x -= 4;
    addAndMakeVisible(*_bottomArrow);
    
    _animator.fadeOut(_topArrow.get(), 1);
    _animator.fadeOut(_bottomArrow.get(), 1);
}

void signalLabel::paint(Graphics& g)
{
    _topArrow->setY(_topArrowHeight);
    
    g.setColour(Colours::lightgrey);
    g.setFont(labelFont);
        
    if(_displayLevelFloat > -10 && _displayLevelFloat < 0)
        g.drawText(_displayLevelString.substring(0,2),
                   _x,
                   _y,
                   50,
                   12,
                   Justification::left);
    else if(_displayLevelFloat > 0)
        g.drawText(_displayLevelString.substring(0,1),
                   _x,
                   _y,
                   50,
                   12,
                   Justification::left);
    else
        g.drawText(_displayLevelString.substring(0,3),
                   _x,
                   _y,
                   50,
                   12,
                   Justification::left);
    
    if(_displayLevelFloat <= -100 && _fadedIn == true)
    {
        _animator.fadeOut(_topArrow.get(), 500);
        _animator.fadeOut(_bottomArrow.get(), 500);
        _fadedIn = false;
    }
    else if(_displayLevelFloat > -90 && _fadedIn == false)
    {
        _animator.fadeIn(_topArrow.get(), 500);
        _animator.fadeIn(_bottomArrow.get(), 500);
        _fadedIn = true;
    }
}

void signalLabel::timerCallback()
{
    repaint();
}

void signalLabel::startTimer()
{
    startTimerHz(24);
}

void signalLabel::setTextY(float coordinate)
{
    _y = coordinate;
}

void signalLabel::setDisplayLevel(float displayLevel)
{
    if(displayLevel >= 0)
        _displayLevelFloat = -0.01;
    else
        _displayLevelFloat = displayLevel;
    
    _displayLevelString = static_cast<String>(_displayLevelFloat);
}

void signalLabel::setTopArrowHeight(int height)
{
    _topArrowHeight = height;
}

void signalLabel::setBottomArrowHeight(int height)
{
    _bottomArrowHeight = height;
}
