/*
  ==============================================================================

    UI-Methods.cpp
    Created: 20 Jan 2024 9:15:37am
    Author:  Jeff

  ==============================================================================
*/

#include "PluginEditor.h"
#include "UI-Methods.h"
UIMethods::UIMethods(LameAmpAudioProcessor& processor) : audioProcessor(processor) {}

void UIMethods::createKnob(juce::Component& component, juce::Slider& slider, juce::Label& label, juce::Colour color, const juce::String& id, const juce::String& name, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, double min, double max, double increment)
{
    component.addAndMakeVisible(slider);
    applyStyle(slider, color);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.mTreeState, id, slider);
    slider.setRange(min, max, increment);
    slider.setName(name);
    slider.setPopupDisplayEnabled(true, true, &component, 2000);
}

void UIMethods::applyStyle(juce::Slider& slider, juce::Colour color)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    shadowProperties.radius = 16;
    shadowProperties.offset = juce::Point<int>(-1, 3);
    dialShadow.setShadowProperties(shadowProperties);

    // Remove border around label
    slider.setColour(0x1001200, juce::Colour::fromFloatRGBA(0, 0, 0, 0.85f));
    slider.setColour(0x1001300, juce::Colour::fromFloatRGBA(255, 255, 255, 0.75));
    slider.setColour(0x1001310, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.65));
    slider.setColour(0x1001311, juce::Colour::fromFloatRGBA(0, 0, 0, 0.5));
    slider.setColour(0x1001400, juce::Colour::fromFloatRGBA(255, 255, 255, 0));
    slider.setColour(0x1001700, juce::Colour::fromFloatRGBA(255, 255, 255, 0.0f));
    slider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    slider.setDoubleClickReturnValue(true, 0.0);
    lameKnob.color = color;
    slider.setLookAndFeel(&lameKnob);
    slider.setComponentEffect(&dialShadow);
}

void UIMethods::applyLabelStyle(juce::Component component, juce::String text, juce::Label& label)
{
    component.addAndMakeVisible(label);
    label.setText(text, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);

    // Set label colors directly
    label.setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    label.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25));
    label.setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
}

void UIMethods::createToggleButton(juce::Component& component, juce::TextButton& button, const juce::String& name, const juce::String& id)
{
    component.addAndMakeVisible(&button);
    button.setButtonText(name);
    button.setClickingTogglesState(true);
    button.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
    button.setColour(0x1000c00, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    button.setColour(0x1000101, juce::Colours::lightgoldenrodyellow.darker(0.2f));
    button.setColour(0x1000102, juce::Colours::black.brighter(0.1));
    button.setColour(0x1000103, juce::Colours::black.brighter(0.1));
}

void UIMethods::createImageToggleButton(juce::Component& component, juce::ImageButton& button, const juce::String& name, const juce::String& id)
{
    component.addAndMakeVisible(&button);
    button.setClickingTogglesState(true);

}
void LameAmpAudioProcessorEditor::createButton(juce::TextButton& button, Modes displayMode, const juce::String& name)
{
    addAndMakeVisible(&button);

    button.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
    
    button.setButtonText(name);
    button.setTooltip(name);
    button.setColour(0x1000c00, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    button.setColour(0x1000102, juce::Colours::black.brighter(0.1));
    button.setColour(0x1000103, juce::Colours::black.brighter(0.1));
    button.onClick = [this, displayMode, &button, &name]() {
        mode = displayMode;

        repaint();
        resized();
        };
    
}