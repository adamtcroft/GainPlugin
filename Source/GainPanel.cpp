/*
  ==============================================================================

    GainPanel.cpp
    Created: 2 May 2020 11:45:19pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "GainPanel.h"

GainPanel::GainPanel(GainPluginAudioProcessor* inputProcessor)
:   PanelBase(inputProcessor)
{
    setSize(PLUGIN_WIDTH, PLUGIN_HEIGHT);
    
    _grip = std::make_unique<sliderGrip>(inputProcessor);
    _grip->setBounds((getWidth() * 0.5) - (SLIDER_WIDTH * 0.5),
                     (getHeight() * 0.45) - (SLIDER_HEIGHT * 0.5),
                     SLIDER_WIDTH,
                     SLIDER_HEIGHT);
    addAndMakeVisible(*_grip);
    
    _vuMeter = std::make_unique<vuMeter>(inputProcessor, SLIDER_WIDTH, SLIDER_HEIGHT);
    _vuMeter->setBounds((getWidth() * 0.5) - (SLIDER_WIDTH * 0.5),
                        (getHeight() * 0.45) - (SLIDER_HEIGHT * 0.5),
                        SLIDER_WIDTH,
                        SLIDER_HEIGHT);
    _vuMeter->setParameterID(Parameter_Gain);
    addAndMakeVisible(*_vuMeter);
    
    _slider = std::make_unique<ParameterSlider>(_processor->_parameters, parameterIDs[Parameter_Gain]);
    _slider->setBounds((getWidth() * 0.5) - (SLIDER_WIDTH * 0.5),
                       (getHeight() * 0.45) - (SLIDER_HEIGHT * 0.5),
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
    
    _vuMeter->setFillHeight(_slider->getValue());
    
    g.setColour(Colours::white);
    g.drawText("RMS: ",
               (getWidth() * 0.5) - (SLIDER_WIDTH * 0.5),
               10,
               SLIDER_WIDTH,
               10,
               Justification::centred);
    repaint();
}
