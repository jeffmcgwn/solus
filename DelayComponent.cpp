/*
  ==============================================================================

    DelayComponent.cpp
    Created: 24 Jan 2024 7:03:52pm
    Author:  Jeff

  ==============================================================================
*/

#include "DelayComponent.h"
#include "PluginProcessor.h"
#include "LameKnob.h"
#include "Globals.h"
#include "UI-Methods.h"
//==============================================================================
DelayComponent::DelayComponent(LameAmpAudioProcessor& p) : audioProcessor(p), pedalComponent(p, "Delay", toggleBtn, delayToggleID, juce::Colours::azure, juce::Colours::darkgrey), uiMethods(p)
{
    addAndMakeVisible(pedalComponent);
    pedalComponent.addBackground(animeOverlay);
    uiMethods.createKnob(*this, delayRateSlider, delayRateSliderLabel, juce::Colours::darkgrey, delayRateID, "Rate", delayRateAttach, 0.0f, 1000.0f);
    uiMethods.createKnob(*this, delayMixSlider, delayMixSliderLabel, juce::Colours::darkgrey, delayMixID, "Mix", delayMixAttach, 0.0f, 1.5f, 0.02f);
    uiMethods.createKnob(*this, delayFeedbackSlider, delayFeedbackSliderLabel, juce::Colours::darkgrey, delayFeedbackID, "Feedback", delayFeedbackAttach, 0.0f, 1.0f, 0.02f);
    uiMethods.createKnob(*this, delaySyncRateSlider, delaySyncRateSliderLabel, juce::Colours::darkgrey, delaySyncRateID, "Rate", delaySyncRateAttach, 0.0f, 12.0f, 1.0f);
    delaySyncRateSlider.textFromValueFunction = [this](double value) {
        return delaySubdivisions[static_cast<int>(value)];
        };

    uiMethods.createImageToggleButton(*this, toggleSyncBtn, "Toggle Sync", delaySyncToggleID);
    toggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.mTreeState, delaySyncToggleID, toggleSyncBtn);

    // Add label to toggle sync btn
    addAndMakeVisible(toggleSyncBtnLabel);
    toggleSyncBtnLabel.setText("Sync", juce::dontSendNotification);
    toggleSyncBtnLabel.attachToComponent(&toggleSyncBtn, false);
    toggleSyncBtnLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgrey);
    toggleSyncBtnLabel.setJustificationType(juce::Justification::centred);
    toggleSyncBtnLabel.setBounds(20, 120, 100, 20);
    // Make toggle sync btn appear below the button
    toggleSyncBtnLabel.setTopLeftPosition(toggleSyncBtn.getX(), toggleSyncBtn.getY() + 60);
    toggleSyncBtn.onClick = [this]() {
        initSync();
        };
    initSync();
    toggleSyncBtn.setSize(22, 60);
    // Resize normalButton
    normalButton = normalButton.rescaled(22, 60);
    downButton = downButton.rescaled(22, 60);
    setSize(200, 400);
}

DelayComponent::~DelayComponent()
{

}

//==============================================================================
void DelayComponent::paint(juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    // Add animeOverlay to background
    g.drawImage(animeOverlay, background.toFloat());

    if (audioProcessor.mTreeState.getRawParameterValue(delaySyncToggleID)->load()) {

        toggleSyncBtn.setImages(false, false, false, normalButton, 1.0f, {}, normalButton, 1.0f, {}, normalButton, 1.0f, {});
    }
    else {
        toggleSyncBtn.setImages(false, false, false, downButton, 1.0f, {}, downButton, 1.0f, {}, downButton, 1.0f, {});
    }

}

void DelayComponent::initSync()
{
    bool sync = audioProcessor.mTreeState.getRawParameterValue(delaySyncToggleID)->load();
    delaySyncRateSlider.setVisible(sync);
    delayRateSlider.setVisible(!sync);
}

void DelayComponent::resized()
{
    // Master bounds object
    juce::Rectangle<int> bounds = getLocalBounds();
    // Make the overall master bounds smaller
    bounds = bounds.reduced(1.2);
    // Place knobs side by side
    int knobWidth = bounds.getWidth() / 2;

    pedalComponent.setBounds(getX(), getY(), getWidth(), getHeight());
    //delayMixSlider.setBounds(bounds.getCentreX() - bounds.getCentreX()/2, bounds.getCentreY() + knobWidth/5, knobWidth, knobWidth);
    //toggleSyncBtn.setBounds(bounds.getCentreX() - bounds.getCentreX() / 2, bounds.getCentreY() + knobWidth / 2, knobWidth / 3, knobWidth);

    juce::FlexBox flexboxColumnOne;
    flexboxColumnOne.flexDirection = juce::FlexBox::Direction::column;
    flexboxColumnOne.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxColumnOne.alignContent = juce::FlexBox::AlignContent::center;

    juce::Array<juce::FlexItem> itemArrayColumnOne;
    itemArrayColumnOne.add(juce::FlexItem(knobWidth, knobWidth, delayRateSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .23, 0, 0, 0)));
    itemArrayColumnOne.add(juce::FlexItem(knobWidth, knobWidth, delayMixSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .05, 0, 0, 0)));


    flexboxColumnOne.items = itemArrayColumnOne;
    flexboxColumnOne.performLayout(bounds.removeFromLeft(bounds.getWidth() / 2));

    juce::FlexBox flexboxColumnTwo;
    flexboxColumnTwo.flexDirection = juce::FlexBox::Direction::column;
    flexboxColumnTwo.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxColumnTwo.alignContent = juce::FlexBox::AlignContent::center;

    juce::Array<juce::FlexItem> itemArrayColumnTwo;
    itemArrayColumnTwo.add(juce::FlexItem(knobWidth, knobWidth, delayFeedbackSlider).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .23, 0, 0, 0)));
    itemArrayColumnTwo.add(juce::FlexItem(knobWidth, knobWidth, toggleSyncBtn).withMargin(juce::FlexItem::Margin(bounds.getHeight() * .05, 0, 0, 0)));

    flexboxColumnTwo.items = itemArrayColumnTwo;
    flexboxColumnTwo.performLayout(bounds.removeFromRight(knobWidth));
    delaySyncRateSlider.setBounds(delayRateSlider.getBounds());
    toggleSyncBtnLabel.setTopLeftPosition(toggleSyncBtn.getX(), toggleSyncBtn.getY() + 80);
    // Make the columns smaller

}
