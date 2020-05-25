/*
  ==============================================================================

    GainPanel.h
    Created: 2 May 2020 11:45:19pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"
#include "ParameterSlider.h"
#include "vuMeter.h"
#include "sliderGrip.h"

class GainPanel : public PanelBase
{
public:
    GainPanel(GainPluginAudioProcessor* inputProcessor);
    ~GainPanel() = default;
    
    void paint(Graphics& g) override;
    static int getSliderWidth();
    static int getSliderHeight();

private:
    std::unique_ptr<ParameterSlider> _slider;
    std::unique_ptr<vuMeter> _vuMeter;
    std::unique_ptr<sliderGrip> _grip;
    int _sliderX, _sliderY;
    
};
