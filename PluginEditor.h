/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LameKnob.h"
#include "HeadComponent.h" 
#include "ReverbComponent.h" 
#include "PedalComponent.h" 
#include "DelayComponent.h"
#include "CabComponent.h"
#include "GateComponent.h"
#include "CleanGateComponent.h"
#include "PedalRow.h"
//==============================================================================
/**
*/
class LameAmpAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LameAmpAudioProcessorEditor (LameAmpAudioProcessor&);
    ~LameAmpAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void createKnob(juce::Component& component, juce::Slider& slider, juce::Label& label, const juce::String& id, const juce::String& name, std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, double min = 0.0f, double max = 24.0f);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::TextButton cabToggle, cleanToggle, pedalToggle, ampToggle;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> cabToggleAttach, cleanToggleAttach, reverbToggleAttach, ampToggleAttach;
    juce::Label gainSliderLabel, volumeSliderLabel, reverbSliderLabel, lowSliderLabel, midSliderLabel, highSliderLabel, lowCleanSliderLabel, midCleanSliderLabel, highCleanSliderLabel, volumeCleanSliderLabel, gainCleanSliderLabel, reverbRoomSizeSliderLabel, reverbDampingSliderLabel, reverbWidthSliderLabel;
    juce::TextButton* buttons[3] { &cabToggle, &pedalToggle, &ampToggle};
    // Arrays for sliders and labels
    juce::Label labels[6];
    
    LameKnob lameKnob;
    juce::DropShadow shadowProperties;
    juce::Image backgroundImgDist, backgroundImg;
    juce::DropShadowEffect dialShadow;
    void applyStyle(juce::Slider& slider);
    void applyLabelStyle(juce::String text, juce::Label& label);
    UIMethods uiMethods;
    LameAmpAudioProcessor& audioProcessor;
    juce::FlexBox flexboxRow;
    HeadComponent headComponent;
    ReverbComponent reverbComponent;
    DelayComponent delayComponent;
    CabComponent cabComponent;
    GateComponent gateComponent;
    CleanGateComponent cleanGateComponent;
    enum class Modes { Amp = 1,Cab = 2, Pedals = 3 };
    enum Modes mode = Modes::Amp;
    void createButton(juce::TextButton& button, Modes displayMode, const juce::String& name);
    void setModeButtonColors();
    PedalRow pedalRow;
    juce::ImageButton cabBtn;
    juce::Image cabOnBtn = juce::ImageCache::getFromMemory(BinaryData::cabOn_png, BinaryData::cabOn_pngSize);
    juce::Image cabOffBtn = juce::ImageCache::getFromMemory(BinaryData::cabOff_png, BinaryData::cabOff_pngSize);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LameAmpAudioProcessorEditor)
};
