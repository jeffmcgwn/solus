/*
  ==============================================================================

    CabComponent.cpp
    Created: 25 Jan 2024 5:26:31pm
    Author:  Jeff

  ==============================================================================
*/

#include "CabComponent.h"
#include "PedalComponent.h"
CabComponent::CabComponent(LameAmpAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(loadBtn);
    addAndMakeVisible(irName);

    if (audioProcessor.savedFile.existsAsFile())
    {
        irName.setText(audioProcessor.savedFile.getFileName(), juce::dontSendNotification);
    }
    else {
        irName.setText("Stock cab", juce::dontSendNotification);
    }

    loadBtn.setButtonText("Load IR");

    loadBtn.onClick = [this]()
        {
            fileChooser = std::make_unique<juce::FileChooser>("Choose file", audioProcessor.root, "*");

            const auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectDirectories;
            
            fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
                {
                    juce::File result(chooser.getResult());

                    if (result.getFileExtension() == ".wav" | result.getFileExtension() == ".mp3")
                    {
                        audioProcessor.savedFile = result;
                        audioProcessor.root = result.getParentDirectory().getFullPathName();
                        audioProcessor.mTreeState.state.setProperty("irName", result.getFullPathName(), nullptr);
                        audioProcessor.mTreeState.state.setProperty("root", result.getParentDirectory().getFullPathName(), nullptr);
                        audioProcessor.mSpeakerModule.reset();

                        audioProcessor.mSpeakerModule.loadImpulseResponse(result, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
                        irName.setText(result.getFileName(), juce::dontSendNotification);
                        this->resized();
                    }
                });
        };
    setSize(800, 600);
}

void CabComponent::paint(juce::Graphics& g) {
    juce::Image backgroundImg = juce::ImageCache::getFromMemory(BinaryData::cabShad_png, BinaryData::cabShad_pngSize);
    backgroundImg = backgroundImg.rescaled(getWidth() * .8, getHeight() * .8);
    g.drawImageWithin(backgroundImg, 38, 0, getWidth(), getHeight() - 70, juce::RectanglePlacement::stretchToFit);
}

CabComponent::~CabComponent()
{

}

void CabComponent::resized()
{
    juce::Rectangle bounds = getLocalBounds();

    const auto btnX = getWidth() * 0.45;
    const auto btnY = getHeight() * 0.1;
    const auto btnWidth = getWidth() * 0.1;
    const auto btnHeight = btnWidth * 0.4;
    const auto numLetters = irName.getText().length();
    loadBtn.setBounds(bounds.getCentreX() - btnWidth / 2 - 5, btnY, btnWidth, btnHeight);
    irName.setBounds(bounds.getCentreX() - (numLetters * 5 - 4), btnY + btnHeight, btnWidth * 2, btnHeight);
}