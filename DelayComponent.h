/*
  ==============================================================================

    DelayComponent.h
    Created: 24 Jan 2024 7:04:04pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "LameKnob.h"
#include "PedalComponent.h"
#include "UI-Methods.h"
class DelayComponent : public juce::Component
{
public:
    DelayComponent(LameAmpAudioProcessor& p);
    ~DelayComponent() override;

    void paint(juce::Graphics& g) override;
    juce::String getTextFromValue(double value);
    void resized() override;

private:
    juce::Slider delayRateSlider, delayMixSlider, delayFeedbackSlider, delaySyncRateSlider;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> delayRateAttach, delayMixAttach, delayFeedbackAttach, delaySyncRateAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> toggleAttach, delaySyncToggleAttach;
    juce::Label delayRateSliderLabel, delayMixSliderLabel, delayFeedbackSliderLabel, delaySyncRateSliderLabel, toggleSyncBtnLabel;
    juce::TextButton toggleBtn, delaySyncToggleBtn;
    LameAmpAudioProcessor& audioProcessor;
    juce::FlexBox flexboxRow;
    PedalComponent pedalComponent;
    juce::TooltipWindow tooltipWindow;
    UIMethods uiMethods;
    void initSync();
    const juce::StringArray delaySubdivisions{ "16th", "16th Triplet", "16th Dotted",
"8th", "8th Triplet", "8th Dotted", "Quarter", "Quarter Triplet", "Quarter Dotted",
"Half", "Half Triplet", "Half Dotted", "Whole" };
    // Add any member variables or methods you need
    juce::ImageButton toggleSyncBtn;
    juce::Image normalButton = juce::ImageCache::getFromMemory(BinaryData::onswitch_png, BinaryData::onswitch_pngSize);
    juce::Image downButton = juce::ImageCache::getFromMemory(BinaryData::offswitch_png, BinaryData::offswitch_pngSize);
    juce::Image animeOverlay = juce::ImageCache::getFromMemory(BinaryData::animeOverlay_png, BinaryData::animeOverlay_pngSize);
};