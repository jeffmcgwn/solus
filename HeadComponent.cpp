/*
  ==============================================================================

    HeadComponent.cpp
    Created: 17 Jan 2024 8:59:54am
    Author:  Jeff

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "HeadComponent.h"
#include "LameKnob.h"
#include "Globals.h"
#include "PluginEditor.h"

//==============================================================================
HeadComponent::HeadComponent(LameAmpAudioProcessor& p) : audioProcessor(p), uiMethods(p)
{
    addAndMakeVisible(&cleanToggle);
    cleanToggle.setButtonText("Channel");
    cleanToggle.setClickingTogglesState(true);
    cleanToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.mTreeState, channelToggleID, cleanToggle);
    cleanToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
    cleanToggle.setColour(0x1000c00, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    cleanToggle.setColour(0x1000101, juce::Colours::lightgoldenrodyellow.darker(0.2f));
    cleanToggle.setColour(0x1000102, juce::Colours::black.brighter(0.1));
    cleanToggle.setColour(0x1000103, juce::Colours::black.brighter(0.1));
    cleanToggle.onClick = [this]() {
        repaint();
        resized();
    };
    uiMethods.createKnob(*this, gainSlider, gainSliderLabel, juce::Colours::lightblue, gainID, "Gain", gainAttach, 0.0f, 40.0f);
    uiMethods.createKnob(*this, volumeSlider, volumeSliderLabel, juce::Colours::lightblue, outputID, "Volume", outputAttach, -24.0f, 24.0f);
    uiMethods.createKnob(*this, reverbSlider, reverbSliderLabel, juce::Colours::lightblue, reverbWetLevelID, "Reverb", reverbAttach, 0.0f, 1.0f, 0.01f);
    uiMethods.createKnob(*this, lowSlider, lowSliderLabel, juce::Colours::lightblue, lowFilterID, "Low", lowAttach, -12.0f, 12.0f);
    uiMethods.createKnob(*this, midSlider, midSliderLabel, juce::Colours::lightblue, midFilterID, "Mid", midAttach, -12.0f, 12.0f);
    uiMethods.createKnob(*this, highSlider, highSliderLabel, juce::Colours::lightblue, highFilterID, "High", highAttach, -12.0f, 12.0f);
    uiMethods.createKnob(*this, volumeCleanSlider, volumeCleanSliderLabel, juce::Colours::lightblue, tubeOutputGainID, "Volume", volumeCleanAttach, -24.0f, 24.0f);
    uiMethods.createKnob(*this, gainCleanSlider, gainCleanSliderLabel, juce::Colours::lightblue, tubeInputGainID, "Gain", gainCleanAttach, 0.0f, 24.0f);
    uiMethods.createKnob(*this, lowCleanSlider, lowCleanSliderLabel, juce::Colours::lightblue, lowCleanFilterID, "Low", lowCleanAttach, -12.0f, 12.0f);
    uiMethods.createKnob(*this, midCleanSlider, midCleanSliderLabel, juce::Colours::lightblue, midCleanFilterID, "Mid", midCleanAttach, -12.0f, 12.0f);
    uiMethods.createKnob(*this, highCleanSlider, highCleanSliderLabel, juce::Colours::lightblue, highCleanFilterID, "High", highCleanAttach, -12.0f, 12.0f);

    setSize(800, 600);
}

HeadComponent::~HeadComponent()
{

}

//==============================================================================
void HeadComponent::paint(juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();

    juce::Image backgroundImgDist = juce::ImageCache::getFromMemory(BinaryData::solusHead_png, BinaryData::solusHead_pngSize);
    juce::Image backgroundImgClean = juce::ImageCache::getFromMemory(BinaryData::solusHeadWhite_png, BinaryData::solusHeadWhite_pngSize);

    if (!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load()) {
        g.drawImageWithin(backgroundImgDist, 0, getHeight() / 6, getWidth(), getHeight() / 1.5 - 4, juce::RectanglePlacement::stretchToFit);
    }
    else {
        g.drawImageWithin(backgroundImgClean, 0,getHeight() / 6, getWidth(), getHeight() / 1.5 - 4, juce::RectanglePlacement::stretchToFit);
    }
        gainSlider.setVisible(!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        lowSlider.setVisible(!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        midSlider.setVisible(!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        highSlider.setVisible(!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        volumeSlider.setVisible(!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());

        gainCleanSlider.setVisible(audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        lowCleanSlider.setVisible(audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        midCleanSlider.setVisible(audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        highCleanSlider.setVisible(audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
        volumeCleanSlider.setVisible(audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load());
}

void HeadComponent::resized()
{
    // Master bounds object
    juce::Rectangle<int> bounds = getLocalBounds();

    // Place knobs side by side
    int knobWidth = bounds.getWidth() / 18;

    // Show alert that shows the height and width of the bounds
    juce::FlexBox flexboxRow;
    flexboxRow.flexDirection = juce::FlexBox::Direction::row;
    flexboxRow.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxRow.alignContent = juce::FlexBox::AlignContent::flexStart;
    flexboxRow.justifyContent = juce::FlexBox::JustifyContent::center;
    juce::Array<juce::FlexItem> itemArrayRow;
    if (!audioProcessor.mTreeState.getRawParameterValue(channelToggleID)->load()) {
        itemArrayRow.add(juce::FlexItem(knobWidth, 10, gainSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, lowSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, midSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, highSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, volumeSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, reverbSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
    }
    else {
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, gainCleanSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, lowCleanSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, midCleanSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, highCleanSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, volumeCleanSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
        itemArrayRow.add(juce::FlexItem(knobWidth, 80, reverbSlider).withMargin(juce::FlexItem::Margin(0, 32, 0, 0)));
    }
    flexboxRow.items = itemArrayRow;
    flexboxRow.performLayout(bounds.removeFromBottom(bounds.getHeight() / 1.6));
    int h = reverbSlider.getY();
    int w = reverbSlider.getX();
    int thing = h;

    cleanToggle.setBounds(reverbSlider.getX() + knobWidth * 2, reverbSlider.getY() * 1.75, 72, 32);

}
