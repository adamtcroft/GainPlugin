/*
  ==============================================================================

    sliderGrip.cpp
    Created: 13 May 2020 7:41:17pm
    Author:  Adam T. Croft

  ==============================================================================
*/

#include "sliderGrip.h"

sliderGrip::sliderGrip(GainPluginAudioProcessor* inputProcessor)
:   _processor(inputProcessor)
{
    
}

void sliderGrip::paint(Graphics& g)
{
    int position = jmap(static_cast<float>(_sliderValue),
                        static_cast<float>(SLIDER_HEIGHT),
                        0.f);
        
    g.setColour(Colours::white);
    g.fillRect((getWidth() * 0.5) - (SLIDER_WIDTH * 0.5),
               position,
               SLIDER_WIDTH,
               250);
    repaint();
}
