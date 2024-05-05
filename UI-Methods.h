/*
  ==============================================================================

    UI-Methods.h
    Created: 28 Jan 2024 1:31:34pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LameKnob.h"

class UIMethods
{
public:
    UIMethods(LameAmpAudioProcessor& processor); // Constructor
    void createKnob(juce::Component& component, juce::Slider& slider, juce::Label& label, juce::Colour color, const juce::String& id, const juce::String& name, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, double min = 0.0f, double max = 24.0f, double increment = 0.1f);
    void applyStyle(juce::Slider& slider, juce::Colour color);
    void applyLabelStyle(juce::Component component, juce::String text, juce::Label& label);
    void createToggleButton(juce::Component& component, juce::TextButton& button, const juce::String& name, const juce::String& id);
    void createImageToggleButton(juce::Component& component, juce::ImageButton& button, const juce::String& name, const juce::String& id);

private:
    LameAmpAudioProcessor& audioProcessor;
    LameKnob lameKnob;
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    juce::StringArray delaySubdivisions{ "16th", "16th Triplet", "16th Dotted",
    "8th", "8th Triplet", "8th Dotted", "Quarter", "Quarter Triplet", "Quarter Dotted",
    "Half", "Half Triplet", "Half Dotted" };
};

