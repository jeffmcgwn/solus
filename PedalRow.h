/*
  ==============================================================================

    PedalRow.h
    Created: 19 Apr 2024 10:16:39am
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "DelayComponent.h"
#include "GateComponent.h"
#include "CleanGateComponent.h"
#include "ReverbComponent.h"
// Make a class for the pedal row
class PedalRow : public juce::Component
{
public:
    PedalRow(LameAmpAudioProcessor& p);
    ~PedalRow() override;

    void paint(juce::Graphics& g) override;
    void resized() override;


private:
    LameAmpAudioProcessor& audioProcessor;
    DelayComponent delayComponent;
    GateComponent gateComponent;
    CleanGateComponent cleanGateComponent;
    ReverbComponent reverbComponent;
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect pedalShadow;
};