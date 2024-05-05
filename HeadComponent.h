/*
  ==============================================================================

    HeadComponent.h
    Created: 17 Jan 2024 9:00:03am
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LameKnob.h"
#include "UI-Methods.h"
class HeadComponent : public juce::Component
{
public:
    HeadComponent(LameAmpAudioProcessor& p);
    ~HeadComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Slider gainSlider, volumeSlider, reverbSlider, lowSlider, midSlider, highSlider;
    juce::Slider volumeCleanSlider, gainCleanSlider, lowCleanSlider, midCleanSlider, highCleanSlider;
    std::vector<juce::Slider*> distSliders = { &gainSlider, &volumeSlider, &reverbSlider, &lowSlider, &midSlider, &highSlider };
    std::vector<juce::Slider*> cleanSliders = { &volumeCleanSlider, &gainCleanSlider, &lowCleanSlider, &midCleanSlider, &highCleanSlider };
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> gainAttach, outputAttach, reverbAttach, lowAttach, midAttach, highAttach, lowCleanAttach, midCleanAttach, highCleanAttach, volumeCleanAttach, gainCleanAttach;
    juce::TextButton cabToggle, cleanToggle;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> cabToggleAttach, cleanToggleAttach;
    juce::Label gainSliderLabel, volumeSliderLabel, reverbSliderLabel, lowSliderLabel, midSliderLabel, highSliderLabel, lowCleanSliderLabel, midCleanSliderLabel, highCleanSliderLabel, volumeCleanSliderLabel, gainCleanSliderLabel;

    juce::Image backgroundImgDist;
    LameAmpAudioProcessor& audioProcessor;
    juce::FlexBox flexboxRow;
    UIMethods uiMethods;
    // Add any member variables or methods you need
};

