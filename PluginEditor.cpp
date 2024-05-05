/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LameKnob.h"
#include "Globals.h"
#include "UI-Methods.h"
//==============================================================================
LameAmpAudioProcessorEditor::LameAmpAudioProcessorEditor (LameAmpAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), headComponent(p), reverbComponent(p), delayComponent(p), cabComponent(p), gateComponent(p), cleanGateComponent(p), uiMethods(p), pedalRow(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    shadowProperties.radius = 16;
    shadowProperties.offset = juce::Point<int>(-1, 3);
    dialShadow.setShadowProperties(shadowProperties);
    addAndMakeVisible(&headComponent);
    addAndMakeVisible(&cabComponent);
    addAndMakeVisible(&pedalRow);
    createButton(cabToggle, Modes::Cab, "Cab");
    createButton(pedalToggle, Modes::Pedals, "Pedals");
    createButton(ampToggle, Modes::Amp, "Amp");


    cabBtn.setImages(false, false, false, cabOnBtn, 1.0f, {}, cabOnBtn, 1.0f, {}, cabOnBtn, 1.0f, {});
    cabBtn.setSize(22, 60);
    // Resize normalButton
    cabOnBtn = cabOnBtn.rescaled(22, 60);
    cabOffBtn = cabOffBtn.rescaled(22, 60);
    addAndMakeVisible(&cabBtn);
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(420, 480, 1200, 800);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(1.5);
    setSize (800, 600);
}

LameAmpAudioProcessorEditor::~LameAmpAudioProcessorEditor()
{

}

//==============================================================================
void LameAmpAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = AudioProcessorEditor::getLocalBounds();

    g.setFont(14.0f);
    juce::Image backgroundImg;
    if (mode == Modes::Pedals) {
        backgroundImg = juce::ImageCache::getFromMemory(BinaryData::floor_jpg, BinaryData::floor_jpgSize);
    }
    else if (mode == Modes::Amp){
        backgroundImg = juce::ImageCache::getFromMemory(BinaryData::plugin_bg_png, BinaryData::plugin_bg_pngSize);
    }
    else {
		backgroundImg = juce::ImageCache::getFromMemory(BinaryData::cab_bg_png, BinaryData::cab_bg_pngSize);
	}

    g.drawImageWithin(backgroundImg, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

    setModeButtonColors();
}

void LameAmpAudioProcessorEditor::setModeButtonColors()
{
    if (mode == Modes::Amp)
    {
        ampToggle.setColour(0x1000100, juce::Colours::lightgoldenrodyellow.darker(0.2f));
        cabToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
        pedalToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));

    }
    else if (mode == Modes::Cab)
    {
        cabToggle.setColour(0x1000100, juce::Colours::lightgoldenrodyellow.darker(0.2f));
        ampToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
        pedalToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
    }
    else {
        pedalToggle.setColour(0x1000100, juce::Colours::lightgoldenrodyellow.darker(0.2f));
        cabToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
        ampToggle.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
    }
}

void LameAmpAudioProcessorEditor::resized()
{
    // Master bounds object
    juce::Rectangle<int> bounds = getLocalBounds();

    // Place knobs side by side
    int knobWidth = bounds.getWidth() / 16;

    if (mode == Modes::Amp)
    {
        pedalRow.setVisible(false);
        cabComponent.setVisible(false);

        headComponent.setVisible(true);
        headComponent.setBounds(0, 0, getWidth(), getHeight());
    }
    else if (mode == Modes::Cab) {
        headComponent.setVisible(false);
        pedalRow.setVisible(false);
        cabComponent.setVisible(true);
        cabComponent.setBounds(0, 0, getWidth(), getHeight());

    }
    else if (mode == Modes::Pedals) {
        headComponent.setVisible(false);
        cabComponent.setVisible(false);
        pedalRow.setVisible(true);
        pedalRow.setBounds(0, 0, getWidth(), getHeight());
    }


    ampToggle.setBounds(getWidth() / 2 - 36, getHeight() - 40, 72, 32);
    cabToggle.setBounds(ampToggle.getX() - 72, ampToggle.getY(), 72, 32);
    pedalToggle.setBounds(ampToggle.getX() + 72, ampToggle.getY(), 72, 32);
    cabBtn.setBounds(30,30, 22, 60);
}
