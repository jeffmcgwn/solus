/*
  ==============================================================================

    PedalComponent.h
    Created: 18 Jan 2024 9:17:33am
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "LameKnob.h"
#include "UI-Methods.h"
class PedalComponent : public juce::Component
{
public:
    PedalComponent(LameAmpAudioProcessor& p,
        juce::String name,
        juce::TextButton& toggleBtn,
        juce::String toggleID,
        juce::Colour color,
        juce::Colour nameColor,
        juce::Image overlay = juce::Image());
    ~PedalComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void addBackground(juce::Image);
    juce::Slider& createKnob(juce::Component& component, juce::Slider& slider, juce::Label& label, const juce::String& id, const juce::String& name, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, double min, double max, double increment = 0.01f);
    void applyStyle(juce::Slider& slider);
    void applyLabelStyle(juce::String text, juce::Label& label);

private:
    juce::LookAndFeel_V4 lookAndFeel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleAttach;
    juce::TextButton toggleButton;
    LameAmpAudioProcessor& audioProcessor;
    juce::String powerToggleID;
    juce::String pedalName;
    LameKnob lameKnob;
    UIMethods uiMethods;
    juce::DropShadow shadowProperties;
    juce::Image backgroundImgDist;
    juce::Colour backgroundColor;
    juce::Colour pedalNameColor;
    juce::GroupComponent border;
    juce::DropShadowEffect dialShadow;
    juce::ImageButton indicatorLight;
    juce::Image onLight = juce::ImageCache::getFromMemory(BinaryData::onLightNew_png, BinaryData::onLightNew_pngSize);
    juce::Image offLight = juce::ImageCache::getFromMemory(BinaryData::offLightNew_png, BinaryData::offLightNew_pngSize);
    juce::Image pedalOverlay;
    juce::ImageComponent backgroundImage;
    juce::ImageButton powerBtn;
    juce::Image normalButton = juce::ImageCache::getFromMemory(BinaryData::pedalBtnSm_png, BinaryData::pedalBtnSm_pngSize);
    juce::Image downButton = juce::ImageCache::getFromMemory(BinaryData::pedalBtnDownSm_png, BinaryData::pedalBtnDownSm_pngSize);

};