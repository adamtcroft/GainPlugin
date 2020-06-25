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
    _sliderX((PLUGIN_HEIGHT * 0.45) - (SLIDER_HEIGHT * 0.5)),
    _sliderY((PLUGIN_WIDTH * 0.5) - (SLIDER_WIDTH * 0.5)),
    _rmsTextXCoordinate(0.0f),
    _rmsTextYCoordinate(0.0f)
{
    setSize(PLUGIN_WIDTH, PLUGIN_HEIGHT);
    
    _grip = std::make_unique<sliderGrip>(inputProcessor);
    _grip->setBounds(static_cast<int>(_sliderY),
                     static_cast<int>(_sliderX),
                     SLIDER_WIDTH,
                     SLIDER_HEIGHT);
    addAndMakeVisible(*_grip);
    
    _vuMeter = std::make_unique<rmsMeter>(inputProcessor, SLIDER_WIDTH, SLIDER_HEIGHT);
    _vuMeter->setBounds(static_cast<int>(_sliderY),
                        static_cast<int>(_sliderX),
                        SLIDER_WIDTH,
                        SLIDER_HEIGHT);
    _vuMeter->setParameterID(Parameter_Gain);
    addAndMakeVisible(*_vuMeter);
    
    _slider = std::make_unique<ParameterSlider>(_processor->_parameters, parameterIDs[Parameter_Gain]);
    _slider->setBounds(static_cast<int>(_sliderY),
                       static_cast<int>(_sliderX),
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
    _rmsTextYCoordinate = (_vuMeter->getMeterHeight() + _sliderX + SLIDER_HEIGHT+5)/2;
    float rmsDisplayLevelFloat = _processor->getRMSLevelInDecibels();
    
    //K-14
//    rmsDisplayLevelFloat += 14;
    
    String rmsDisplayLevel = static_cast<String>(rmsDisplayLevelFloat);
    auto meterHeight = _vuMeter->getMeterHeight() + static_cast<int>(_sliderX);
    
    if(rmsDisplayLevelFloat <= -100)
    {
        
        g.setColour(Colours::black);
        _rmsTextXCoordinate = getWidth()/3.8;
    }
    else
    {
        _rmsTextXCoordinate = getWidth()/4;
    }
  
    
    if(_rmsTextYCoordinate >= 237)
        g.setColour(Colours::black);
    else
        g.setColour(Colours::lightgrey);

    g.fillRect(getWidth()-55, meterHeight, 10, 2);
    g.fillRect(getWidth()-55, static_cast<int>(_sliderX) + SLIDER_HEIGHT - 3, 10, 2);
    g.fillRect(getWidth()-45, meterHeight, 2, 10);
    g.fillRect(getWidth()-45, static_cast<int>(_sliderX) + SLIDER_HEIGHT - 11, 2, 10);
    
    g.setColour(Colours::lightgrey);
    
    if(rmsDisplayLevelFloat > -10 && rmsDisplayLevelFloat < 0)
    {
        g.drawText(rmsDisplayLevel.substring(0,2),
                   _rmsTextXCoordinate,
                   _rmsTextYCoordinate,
                   getWidth(),
                   12,
                   Justification::centred);
    }
    else if(rmsDisplayLevelFloat > 0)
    {
        g.drawText(rmsDisplayLevel.substring(0,1),
                   _rmsTextXCoordinate,
                   _rmsTextYCoordinate,
                   getWidth(),
                   12,
                   Justification::centred);
    }
    else
    {
        g.drawText(rmsDisplayLevel.substring(0,3),
                   _rmsTextXCoordinate,
                   _rmsTextYCoordinate,
                   getWidth(),
                   12,
                   Justification::centred);
    }

    
    repaint();
}

