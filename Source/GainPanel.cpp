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
    _fadedIn(false)
{
    setSize(PLUGIN_WIDTH, PLUGIN_HEIGHT);
    
    initializeBackground();
    initializeLabels();
    initializeSlider();
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
    
    _rmsLabelLeft->setTextY((_rmsMeterLeft->getMeterHeight() + _sliderY + SLIDER_HEIGHT + 5)/2);
    _rmsLabelLeft->setDisplayLevel(_processor->getRMSLevelInDecibels(0));
    _rmsLabelLeft->setTopArrowHeight(_rmsMeterLeft->getMeterHeight() + static_cast<int>(_sliderY));
    
    _rmsLabelRight->setTextY((_rmsMeterRight->getMeterHeight() + _sliderY + SLIDER_HEIGHT + 5)/2);
    _rmsLabelRight->setDisplayLevel(_processor->getRMSLevelInDecibels(1));
    _rmsLabelRight->setTopArrowHeight(_rmsMeterRight->getMeterHeight() + static_cast<int>(_sliderY));

    _peakLabelLeft->setTextY((_peakMeterLeft->getMeterHeight() + _sliderY + SLIDER_HEIGHT + 5)/2);
    _peakLabelLeft->setDisplayLevel(_processor->getPeakLevelInDecibels(0));
    _peakLabelLeft->setTopArrowHeight(_peakMeterLeft->getMeterHeight() + static_cast<int>(_sliderY));

    _peakLabelRight->setTextY((_peakMeterRight->getMeterHeight() + _sliderY + SLIDER_HEIGHT + 5)/2);
    _peakLabelRight->setDisplayLevel(_processor->getPeakLevelInDecibels(1));
    _peakLabelRight->setTopArrowHeight(_peakMeterRight->getMeterHeight() + static_cast<int>(_sliderY));


    if(_processor->getRMSLevelInDecibels(0) > -93 && _fadedIn == false)
    {
        _animator.fadeIn(_rmsLabelLeft.get(), 400);
        _animator.fadeIn(_rmsLabelRight.get(), 400);
        _animator.fadeIn(_peakLabelLeft.get(), 400);
        _animator.fadeIn(_peakLabelRight.get(), 400);
        _fadedIn = true;
    }
    else if(_processor->getRMSLevelInDecibels(0) <= -100 && _fadedIn == true)
    {
        _animator.fadeOut(_rmsLabelLeft.get(), 500);
        _animator.fadeOut(_rmsLabelRight.get(), 500);
        _animator.fadeOut(_peakLabelLeft.get(), 500);
        _animator.fadeOut(_peakLabelRight.get(), 500);
        _fadedIn = false;
    }

    repaint();
}

void GainPanel::initializeBackground()
{
    // GRIP
    _grip = std::make_unique<sliderGrip>(_processor);
    _grip->setBounds(static_cast<int>(_sliderX),
                     static_cast<int>(_sliderY),
                     SLIDER_WIDTH,
                     SLIDER_HEIGHT);
    addAndMakeVisible(*_grip);
    
    // PEAK METERS
    _peakMeterLeft = std::make_unique<peakMeter>(_processor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 0);
    _peakMeterLeft->setBounds(static_cast<int>(_sliderX),
                          static_cast<int>(_sliderY),
                          SLIDER_WIDTH/2,
                          SLIDER_HEIGHT);
    _peakMeterLeft->startTimer();
    addAndMakeVisible(*_peakMeterLeft);
    
    _peakMeterRight = std::make_unique<peakMeter>(_processor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 1);
    _peakMeterRight->setBounds(static_cast<int>(_sliderX) + SLIDER_WIDTH/2,
                          static_cast<int>(_sliderY),
                          SLIDER_WIDTH/2,
                          SLIDER_HEIGHT);
    _peakMeterRight->startTimer();
    addAndMakeVisible(*_peakMeterRight);

    
    // RMS METERS
    _rmsMeterLeft = std::make_unique<rmsMeter>(_processor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 0);
    _rmsMeterLeft->setBounds(static_cast<int>(_sliderX),
                        static_cast<int>(_sliderY),
                        SLIDER_WIDTH/2,
                        SLIDER_HEIGHT);
    _rmsMeterLeft->startTimer();
    addAndMakeVisible(*_rmsMeterLeft);
    
    _rmsMeterRight = std::make_unique<rmsMeter>(_processor, SLIDER_WIDTH/2, SLIDER_HEIGHT, 1);
    _rmsMeterRight->setBounds(static_cast<int>(_sliderX) + SLIDER_WIDTH/2,
                        static_cast<int>(_sliderY),
                        SLIDER_WIDTH/2,
                        SLIDER_HEIGHT);
    _rmsMeterRight->startTimer();
    addAndMakeVisible(*_rmsMeterRight);
}

void GainPanel::initializeLabels()
{
    _rmsLabelLeft = std::make_shared<signalLabel>(_sliderX - 15, SLIDER_HEIGHT + 9);
    _rmsLabelLeft->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _rmsLabelLeft->startTimer();
    addAndMakeVisible(*_rmsLabelLeft);
    
    _rmsLabelRight = std::make_shared<signalLabel>(_sliderX + SLIDER_WIDTH + 5, SLIDER_HEIGHT + 9, true);
    _rmsLabelRight->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _rmsLabelRight->startTimer();
    addAndMakeVisible(*_rmsLabelRight);

    _peakLabelLeft = std::make_shared<signalLabel>(_sliderX - 35, SLIDER_HEIGHT + 9);
    _peakLabelLeft->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _peakLabelLeft->startTimer();
    addAndMakeVisible(*_peakLabelLeft);

    _peakLabelRight = std::make_shared<signalLabel>(_sliderX + SLIDER_WIDTH + 25, SLIDER_HEIGHT + 9, true);
    _peakLabelRight->setBounds(0, 0, PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _peakLabelRight->startTimer();
    addAndMakeVisible(*_peakLabelRight);
    
    _animator.fadeOut(_rmsLabelLeft.get(), 1);
    _animator.fadeOut(_rmsLabelRight.get(), 1);
    _animator.fadeOut(_peakLabelLeft.get(), 1);
    _animator.fadeOut(_peakLabelRight.get(), 1);
}

void GainPanel::initializeSlider()
{
    _slider = std::make_unique<ParameterSlider>(_processor->_parameters, parameterIDs[Parameter_Gain]);
    _slider->setBounds(static_cast<int>(_sliderX),
                       static_cast<int>(_sliderY),
                       SLIDER_WIDTH,
                       SLIDER_HEIGHT);
    _slider->setColour(_slider->trackColourId, Colours::transparentBlack);
    _slider->setColour(_slider->textBoxOutlineColourId, Colours::transparentBlack);
    addAndMakeVisible(*_slider);
}
