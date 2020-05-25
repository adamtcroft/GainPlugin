/*
  ==============================================================================

    MainPanel.cpp
    Created: 28 Apr 2020 10:50:51pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "MainPanel.h"

MainPanel::MainPanel(GainPluginAudioProcessor* inputProcessor)
: PanelBase(inputProcessor)
{
    setSize(PLUGIN_WIDTH, PLUGIN_HEIGHT);
    
    _gainPanel = std::make_unique<GainPanel>(inputProcessor);
    _gainPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(*_gainPanel);
}
