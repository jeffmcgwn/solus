/*
  ==============================================================================

    CabComponent.h
    Created: 25 Jan 2024 5:26:23pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#pragma once
#include <JuceHeader.h>
#include "LameKnob.h"
class CabComponent : public juce::Component
{
public:
    CabComponent(LameAmpAudioProcessor& p);
    ~CabComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;


private:
    LameAmpAudioProcessor& audioProcessor;
    juce::TextButton loadBtn;
    std::unique_ptr<juce::FileChooser> fileChooser;
    juce::Label irName;
    // Add any member variables or methods you need
};

