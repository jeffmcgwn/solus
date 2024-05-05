/*
  ==============================================================================

    GateComponent.h
    Created: 27 Jan 2024 6:06:23pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "LameKnob.h"
#include "PedalComponent.h"
#include "UI-Methods.h"
class GateComponent : public juce::Component
{
public:
    GateComponent(LameAmpAudioProcessor& p);
    ~GateComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Slider attackSlider, ratioSlider, thresholdSlider, releaseSlider;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> attackAttach, ratioAttach, thresholdAttach, releaseAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> toggleAttach;
    juce::TextButton gateToggle;
    juce::Label attackSliderLabel, ratioSliderLabel, thresholdSliderLabel, releaseSliderLabel;

    juce::Slider* gateSliders[4] = { &attackSlider, &ratioSlider, &thresholdSlider, &releaseSlider };
    juce::TextButton toggleBtn;
    LameKnob lameKnob;
    LameAmpAudioProcessor& audioProcessor;
    juce::FlexBox flexboxRow;
    PedalComponent pedalComponent;
    UIMethods uiMethods;
    juce::Image animeOverlay = juce::ImageCache::getFromMemory(BinaryData::animeGateOverlay_png, BinaryData::animeGateOverlay_pngSize);

    // Add any member variables or methods you need
};