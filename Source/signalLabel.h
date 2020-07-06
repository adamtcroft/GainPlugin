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
    void startTimer();
    void setTextY(float coordinate);
    void setDisplayLevel(float displayLevel);
    void setTopArrowHeight(int height);
    void setBottomArrowHeight(int height);
    
private:
    GainPluginAudioProcessor* _processor;
    float _x, _y, _displayLevelFloat;
    int _topArrowHeight, _bottomArrowHeight;
    String _displayLevelString;
    std::unique_ptr<arrowBracket> _topArrow, _bottomArrow;
};
