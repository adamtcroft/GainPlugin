/*
  ==============================================================================

    signalLabel.h
    Created: 5 Jul 2020 6:02:01pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "GlobalDefines.h"
#include "arrowBracket.h"

class signalLabel : public Component, Timer
{
public:
    signalLabel(int x, int y, bool flip = false);
    ~signalLabel() = default;
    
    void paint(Graphics& g) override;
    void timerCallback() override;
    
    inline void startTimer() { startTimerHz(24); };
    inline void setTextY(float coordinate) { _y = coordinate; };
    inline void setTopArrowHeight(int height) { _topArrowHeight = height; };
    inline void setBottomArrowHeight(int height) { _bottomArrowHeight = height; };
    inline void setDisplayLevel(float displayLevel)
    {
        if(displayLevel >= 0)
            _displayLevelFloat = -0.01;
        else
            _displayLevelFloat = displayLevel;
        
        _displayLevelString = static_cast<String>(_displayLevelFloat);
    }
    
private:
    GainPluginAudioProcessor* _processor;
    float _x, _y, _displayLevelFloat;
    int _topArrowHeight, _bottomArrowHeight;
    String _displayLevelString;
    ComponentAnimator _animator;
    bool _fadedIn;
    std::unique_ptr<arrowBracket> _topArrow, _bottomArrow;
};
