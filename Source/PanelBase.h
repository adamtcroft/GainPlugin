/*
  ==============================================================================

    PanelBase.h
    Created: 28 Apr 2020 10:52:07pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "ParameterSlider.h"
#include "GlobalDefines.h"
#include "HelperFunctions.h"
#include "ParameterList.h"


class PanelBase : public Component
{
public:
    PanelBase(GainPluginAudioProcessor* inputProcessor);
    ~PanelBase() = default;
    
protected:
    GainPluginAudioProcessor* _processor;
};
