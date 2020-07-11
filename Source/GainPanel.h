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
#include "signalLabel.h"

class GainPanel : public PanelBase
{
public:
    GainPanel(GainPluginAudioProcessor* inputProcessor);
    ~GainPanel() = default;
    
    void paint(Graphics& g) override;

private:
    std::unique_ptr<ParameterSlider> _slider;
    std::unique_ptr<rmsMeter> _rmsMeterLeft, _rmsMeterRight;
    std::unique_ptr<peakMeter> _peakMeterLeft, _peakMeterRight;
    std::unique_ptr<sliderGrip> _grip;
    std::shared_ptr<signalLabel> _rmsLabelLeft, _rmsLabelRight, _peakLabelLeft, _peakLabelRight;

    float _sliderX, _sliderY;
    ComponentAnimator _animator;
    bool _fadedIn;
    
    void initializeBackground();
    void initializeLabels();
    void initializeSlider();
};
