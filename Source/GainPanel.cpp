/*
  ==============================================================================

    GainPanel.cpp
    Created: 2 May 2020 11:45:19pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "GainPanel.h"
#include <iomanip>

GainPanel::GainPanel(GainPluginAudioProcessor* inputProcessor)
:   PanelBase(inputProcessor),
    _sliderX((PLUGIN_WIDTH * 0.5) - (SLIDER_WIDTH * 0.5)),
    _sliderY((PLUGIN_HEIGHT * 0.45) - (SLIDER_HEIGHT * 0.5)),
    _rmsTextXCoordinate(0.0f),
    _rmsTextYCoordinate(0.0f),
    _fadedIn(false)
{
    setSize(PLUGIN_WIDTH, PLUGIN_HEIGHT);
    
    _grip = std::make_unique<sliderGrip>(inputProcessor);
    _grip->setBounds(static_cast<int>(_sliderX),
                     static_cast<int>(_sliderY),
                     SLIDER_WIDTH,
                     SLIDER_HEIGHT);
    addAndMakeVisible(*_grip);
    
    _rmsMeterLeft = std::make_unique<rmsMeter>(inputProcessor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 0);
    _rmsMeterLeft->setBounds(static_cast<int>(_sliderX),
                        static_cast<int>(_sliderY),
                        SLIDER_WIDTH/2,
                        SLIDER_HEIGHT);
    _rmsMeterLeft->startTimer();
    addAndMakeVisible(*_rmsMeterLeft);
    
    _rmsLabelLeft = std::make_unique<signalLabel>();
    _rmsLabelLeft->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _rmsLabelLeft->startTimer();
    addAndMakeVisible(*_rmsLabelLeft);

    _rmsMeterRight = std::make_unique<rmsMeter>(inputProcessor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 1);
    _rmsMeterRight->setBounds(static_cast<int>(_sliderX) + SLIDER_WIDTH/2,
                        static_cast<int>(_sliderY),
                        SLIDER_WIDTH/2,
                        SLIDER_HEIGHT);
    _rmsMeterRight->startTimer();
    addAndMakeVisible(*_rmsMeterRight);
    
    _peakMeterLeft = std::make_unique<peakMeter>(inputProcessor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 0);
    _peakMeterLeft->setBounds(static_cast<int>(_sliderX),
                          static_cast<int>(_sliderY),
                          SLIDER_WIDTH/2,
                          SLIDER_HEIGHT);
    _peakMeterLeft->startTimer();
    addAndMakeVisible(*_peakMeterLeft);
    
    _peakMeterRight = std::make_unique<peakMeter>(inputProcessor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 1);
    _peakMeterRight->setBounds(static_cast<int>(_sliderX) + SLIDER_WIDTH/2,
                          static_cast<int>(_sliderY),
                          SLIDER_WIDTH/2,
                          SLIDER_HEIGHT);
    _peakMeterRight->startTimer();
    addAndMakeVisible(*_peakMeterRight);
    
    _slider = std::make_unique<ParameterSlider>(_processor->_parameters, parameterIDs[Parameter_Gain]);
    _slider->setBounds(static_cast<int>(_sliderX),
                       static_cast<int>(_sliderY),
                       SLIDER_WIDTH,
                       SLIDER_HEIGHT);
    _slider->setColour(_slider->trackColourId, Colours::transparentBlack);
    _slider->setColour(_slider->textBoxOutlineColourId, Colours::transparentBlack);
    addAndMakeVisible(*_slider);
}

void GainPanel::paint(Graphics& g)
{
    PanelBase::paint(g);
    
    g.setColour(Colours::black);
    g.fillAll();
    
    if(_slider)
        paintComponentLabel(g, _slider.get(), getWidth());
    
    _grip->setValue(static_cast<float>(_slider->getValue()));
    
    _rmsMeterLeft->setFillHeight(_slider->getValue());
    _rmsMeterRight->setFillHeight(_slider->getValue());
    _peakMeterLeft->setFillHeight(_slider->getValue());
    _peakMeterRight->setFillHeight(_slider->getValue());
    
    _rmsLabelLeft->setY((_rmsMeterLeft->getMeterHeight() + _sliderY + SLIDER_HEIGHT + 5)/2);
    _rmsLabelLeft->setDisplayLevel(_processor->getRMSLevelInDecibels(0));
    
    _rmsLabelLeft->setTopArrowHeight(_rmsMeterLeft->getMeterHeight() + static_cast<int>(_sliderY));
    _rmsLabelLeft->setBottomArrowHeight(SLIDER_HEIGHT + 10);

//    if(rmsDisplayLevelFloat > -90 && _fadedIn == false)
//    {
//        _animator.fadeIn(_rmsLabelLeft.get(), 5000);
//        _fadedIn = true;
//    }

    repaint();
}

