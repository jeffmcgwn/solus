/*
  ==============================================================================

    ReverbComponent.h
    Created: 18 Jan 2024 9:17:25am
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "LameKnob.h"
#include "PedalComponent.h"
#include "UI-Methods.h"
class ReverbComponent : public juce::Component
{
public:
    ReverbComponent(LameAmpAudioProcessor& p);
    ~ReverbComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Slider reverbSlider, reverbRoomSizeSlider, reverbDampingSlider, reverbWidthSlider;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> reverbAttach, reverbRoomSizeAttach, reverbDampingAttach, reverbWidthAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> toggleAttach;
    juce::TextButton reverbToggle;
    juce::Label reverbSliderLabel, reverbRoomSizeSliderLabel, reverbDampingSliderLabel, reverbWidthSliderLabel;

    juce::Slider* reverbSliders[4] = { &reverbRoomSizeSlider, &reverbDampingSlider, &reverbWidthSlider, &reverbSlider };
    juce::TextButton toggleBtn;
    LameAmpAudioProcessor& audioProcessor;
    juce::FlexBox flexboxRow;
    PedalComponent pedalComponent;
    UIMethods uiMethods;
    juce::Image animeOverlay = juce::ImageCache::getFromMemory(BinaryData::animeTreeOverlay_png, BinaryData::animeTreeOverlay_pngSize);
    // Add any member variables or methods you need
};