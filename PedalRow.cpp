/*
  ==============================================================================

    PedalRow.cpp
    Created: 19 Apr 2024 10:16:39am
    Author:  Jeff

  ==============================================================================
*/

#include "PedalRow.h"
PedalRow::PedalRow(LameAmpAudioProcessor& p) : audioProcessor(p), reverbComponent(p), delayComponent(p), gateComponent(p), cleanGateComponent(p)
{
    addAndMakeVisible(&delayComponent);
	addAndMakeVisible(&reverbComponent);
	addAndMakeVisible(&gateComponent);
	addAndMakeVisible(&cleanGateComponent);
    shadowProperties.radius = 100;
    shadowProperties.offset = juce::Point<int>(-100, 30);
    pedalShadow.setShadowProperties(shadowProperties);
    delayComponent.setComponentEffect(&pedalShadow);
	setSize(800, 600);
}

void PedalRow::paint(juce::Graphics& g) {

}

PedalRow::~PedalRow()
{

}

void PedalRow::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();

    delayComponent.setVisible(true);
    reverbComponent.setVisible(true);
    delayComponent.setBounds(bounds.getWidth() / 6 - delayComponent.getWidth() / 2, bounds.getHeight() / 2 - delayComponent.getHeight() / 2 - 16, delayComponent.getWidth(), delayComponent.getHeight());
    reverbComponent.setBounds(bounds.getWidth() - ((bounds.getWidth() / 2) + delayComponent.getWidth() / 2), bounds.getHeight() / 2 - delayComponent.getHeight() / 2 - 16, delayComponent.getWidth(), delayComponent.getHeight());
    if (audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load())
    {
        gateComponent.setVisible(false);
        cleanGateComponent.setVisible(true);
        cleanGateComponent.setBounds(bounds.getWidth() - ((bounds.getWidth() / 6) + delayComponent.getWidth() / 2), bounds.getHeight() / 2 - delayComponent.getHeight() / 2 - 16, delayComponent.getWidth(), delayComponent.getHeight());
    }
    else {
        cleanGateComponent.setVisible(false);
        gateComponent.setVisible(true);
        gateComponent.setBounds(bounds.getWidth() - ((bounds.getWidth() / 6) + delayComponent.getWidth() / 2), bounds.getHeight() / 2 - delayComponent.getHeight() / 2 - 16, delayComponent.getWidth(), delayComponent.getHeight());
    }
}