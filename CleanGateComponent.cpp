/*
  ==============================================================================

    CleanGateComponent.cpp
    Created: 27 Jan 2024 6:06:35pm
    Author:  Jeff

  ==============================================================================
*/

#include "CleanGateComponent.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LameKnob.h"
#include "Globals.h"
CleanGateComponent::CleanGateComponent(LameAmpAudioProcessor& p) : audioProcessor(p), pedalComponent(p, "Gate", toggleBtn, cleanGateToggleID, juce::Colours::darkgrey, juce::Colours::whitesmoke), uiMethods(p)
{

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(pedalComponent);
    pedalComponent.addBackground(animeOverlay);
    uiMethods.createKnob(*this, attackSlider, attackSliderLabel, juce::Colours::whitesmoke, cleanGateAttackID, "Attack", attackAttach, -0.0f, 250.0f);
    uiMethods.createKnob(*this, ratioSlider, ratioSliderLabel, juce::Colours::whitesmoke, cleanGateRatioID, "Ratio", ratioAttach, 1.0f, 10.0f, 1.0f);
    uiMethods.createKnob(*this, thresholdSlider, thresholdSliderLabel, juce::Colours::whitesmoke, cleanGateThresholdID, "Threshold", thresholdAttach, -100.0f, 6.0f);
    uiMethods.createKnob(*this, releaseSlider, releaseSliderLabel, juce::Colours::whitesmoke, cleanGateReleaseID, "Release", releaseAttach, -0.0f, 1500.0f);

    setSize(200, 400);
}

CleanGateComponent::~CleanGateComponent()
{

}

//==============================================================================
void CleanGateComponent::paint(juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
}

void CleanGateComponent::resized()
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
    itemArrayColumnOne.add(juce::FlexItem(knobWidth, knobWidth, attackSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .23, 0, 0, 0)));
    itemArrayColumnOne.add(juce::FlexItem(knobWidth, knobWidth, thresholdSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .05, 0, 0, 0)));


    flexboxColumnOne.items = itemArrayColumnOne;
    flexboxColumnOne.performLayout(bounds.removeFromLeft(getWidth() / 2));

    juce::FlexBox flexboxColumnTwo;
    flexboxColumnTwo.flexDirection = juce::FlexBox::Direction::column;
    flexboxColumnTwo.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxColumnTwo.alignContent = juce::FlexBox::AlignContent::center;

    juce::Array<juce::FlexItem> itemArrayColumnTwo;
    itemArrayColumnTwo.add(juce::FlexItem(knobWidth, knobWidth, releaseSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .23, 0, 0, 0)));
    itemArrayColumnTwo.add(juce::FlexItem(knobWidth, knobWidth, ratioSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .05, 0, 0, 0)));

    flexboxColumnTwo.items = itemArrayColumnTwo;
    flexboxColumnTwo.performLayout(bounds.removeFromRight(knobWidth));
}
