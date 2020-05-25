/*
  ==============================================================================

    MainPanel.h
    Created: 28 Apr 2020 10:50:51pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"
#include "GainPanel.h"

class MainPanel : public PanelBase
{
public:
    MainPanel(GainPluginAudioProcessor* inputProcessor);
    ~MainPanel() = default;
    
private:
    std::unique_ptr<GainPanel> _gainPanel;
};
