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
#include "rmsMeter.h"
#include "peakMeter.h"
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
    std::unique_ptr<rmsMeter> _rmsMeterLeft, _rmsMeterRight;
    std::unique_ptr<peakMeter> _peakMeterLeft, _peakMeterRight;
    std::unique_ptr<sliderGrip> _grip;
    float _sliderX, _sliderY;
    float _rmsTextXCoordinate, _rmsTextYCoordinate;
    float _peakTextXCoordinate, _peakTextYCoordinate;
};
