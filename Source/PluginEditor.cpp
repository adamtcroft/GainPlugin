/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainPluginAudioProcessorEditor::GainPluginAudioProcessorEditor (GainPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (PLUGIN_WIDTH, PLUGIN_HEIGHT);
    _mainPanel = std::make_unique<MainPanel>(&processor);
    addAndMakeVisible(*_mainPanel);
}

GainPluginAudioProcessorEditor::~GainPluginAudioProcessorEditor()
{
}

//==============================================================================
void GainPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void GainPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
