/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 18 Jan 2024 9:17:10am
    Author:  Jeff

  ==============================================================================
*/

#include "ReverbComponent.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LameKnob.h"
#include "Globals.h"

//==============================================================================
ReverbComponent::ReverbComponent(LameAmpAudioProcessor& p) : audioProcessor(p), pedalComponent(p, "Reverb", toggleBtn, reverbToggleID, juce::Colours::blueviolet, juce::Colours::lightblue), uiMethods(p)
{
    addAndMakeVisible(pedalComponent);
    pedalComponent.addBackground(animeOverlay);
    uiMethods.createKnob(*this, reverbSlider, reverbSliderLabel, juce::Colours::lightblue, reverbWetLevelID, "Reverb", reverbAttach, 0.0f, 1.0f, 0.01f);
    uiMethods.createKnob(*this, reverbRoomSizeSlider, reverbRoomSizeSliderLabel, juce::Colours::lightblue, reverbRoomSizeID, "Room Size", reverbRoomSizeAttach, 0.0, 1.0, 0.01f);
    uiMethods.createKnob(*this, reverbDampingSlider, reverbDampingSliderLabel, juce::Colours::lightblue, reverbDampingID, "Damping", reverbDampingAttach, 0.0, 1.0, 0.02f);
    uiMethods.createKnob(*this, reverbWidthSlider, reverbWidthSliderLabel, juce::Colours::lightblue, reverbWidthID, "Width", reverbWidthAttach, 0.0, 1.0, 0.02f);

    setSize(200, 400);
}

ReverbComponent::~ReverbComponent()
{

}

//==============================================================================
void ReverbComponent::paint(juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
}

void ReverbComponent::resized()
{
    // Master bounds object
    juce::Rectangle<int> bounds = getLocalBounds();
    bounds = bounds.reduced(1.2);
    // Place knobs side by side
    int knobWidth = getWidth() / 2;

    pedalComponent.setBounds(getX(), getY(), getWidth(), getHeight());

    juce::FlexBox flexboxColumnOne;
    flexboxColumnOne.flexDirection = juce::FlexBox::Direction::column;
    flexboxColumnOne.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxColumnOne.alignContent = juce::FlexBox::AlignContent::center;

    juce::Array<juce::FlexItem> itemArrayColumnOne;
    itemArrayColumnOne.add(juce::FlexItem(knobWidth, knobWidth, reverbDampingSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .23, 0, 0, 0)));
    itemArrayColumnOne.add(juce::FlexItem(knobWidth, knobWidth, reverbWidthSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .05, 0, 0, 0)));


    flexboxColumnOne.items = itemArrayColumnOne;
    flexboxColumnOne.performLayout(bounds.removeFromLeft(getWidth() / 2));

    juce::FlexBox flexboxColumnTwo;
    flexboxColumnTwo.flexDirection = juce::FlexBox::Direction::column;
    flexboxColumnTwo.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxColumnTwo.alignContent = juce::FlexBox::AlignContent::center;

    juce::Array<juce::FlexItem> itemArrayColumnTwo;
    itemArrayColumnTwo.add(juce::FlexItem(knobWidth, knobWidth, reverbRoomSizeSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .23, 0, 0, 0)));
    itemArrayColumnTwo.add(juce::FlexItem(knobWidth, knobWidth, reverbSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .05, 0, 0, 0)));


    flexboxColumnTwo.items = itemArrayColumnTwo;
    flexboxColumnTwo.performLayout(bounds.removeFromRight(knobWidth));
}
