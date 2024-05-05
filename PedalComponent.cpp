#include "PedalComponent.h"
#include "UI-Methods.h"
PedalComponent::PedalComponent(LameAmpAudioProcessor& p, juce::String name, juce::TextButton& toggleBtn, juce::String toggleID, juce::Colour color, juce::Colour nameColor, juce::Image overlay) : audioProcessor(p), uiMethods(p)
{
    pedalName = name;
    backgroundColor = color;
    pedalNameColor = nameColor;
    powerToggleID = toggleID;
    if (overlay.isValid()) {
		pedalOverlay = overlay;
	}
    border.setColour(0x1005400, juce::Colour::fromFloatRGBA(255, 105, 180, 0.75));
    shadowProperties.radius = 2;
    shadowProperties.offset = juce::Point<int>(-1, 3);
    dialShadow.setShadowProperties(shadowProperties);
    addAndMakeVisible(border);
    backgroundImage.setImage(overlay);
    backgroundImage.setImagePlacement(juce::RectanglePlacement(juce::RectanglePlacement::stretchToFit));
    addAndMakeVisible(backgroundImage);
    uiMethods.createToggleButton(*this, toggleButton, "Power", powerToggleID);
    uiMethods.createImageToggleButton(*this, powerBtn, "Toggle Sync", powerToggleID);
    toggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.mTreeState, toggleID, powerBtn);
    addAndMakeVisible(indicatorLight, 10);
    // Resize normalButton
    onLight = onLight.rescaled(16, 16);
    offLight = offLight.rescaled(16, 16);

    setSize(200, 400);
}

void PedalComponent::addBackground(juce::Image img) {
    img.multiplyAllAlphas(0.3);
    backgroundImage.setImage(img);
    backgroundImage.setImagePlacement(juce::RectanglePlacement(juce::RectanglePlacement::stretchToFit));
    addAndMakeVisible(backgroundImage);
}

void PedalComponent::paint(juce::Graphics& g) {
    juce::Rectangle<int> bounds = getLocalBounds();
    g.setColour(backgroundColor);

    g.fillRoundedRectangle(getX(), getY(), getWidth(), getHeight(), 10.5);
    backgroundImage.setBounds(bounds);
    g.setColour(pedalNameColor);
    g.drawImageWithin(pedalOverlay, bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), juce::RectanglePlacement::stretchToFit);
    //normalButton = normalButton.rescaled(40, 40);
    //downButton = downButton.rescaled(40, 40);
    powerBtn.setImages(false, false, false, normalButton, 1.0f, {}, downButton, 1.0f, {}, normalButton, 1.0f, {});
    float diameter = fmin(bounds.getWidth(), bounds.getHeight());
    float radius = diameter * 0.5;
    g.setFont(radius * 0.5f);
    g.drawSingleLineText(pedalName, bounds.getCentreX(), getY() + radius * 0.5, juce::Justification::centred);
    if (audioProcessor.mTreeState.getRawParameterValue(powerToggleID)->load()) {

        indicatorLight.setImages(false, false, false, onLight, 1.0f, {}, onLight, 1.0f, {}, onLight, 1.0f, {});
    }
    else {
        indicatorLight.setImages(false, false, false, offLight, 1.0f, {}, offLight, 1.0f, {}, offLight, 1.0f, {});
    }
}

PedalComponent::~PedalComponent()
{
}

void PedalComponent::resized()
{
    auto leftMargin = getWidth() * 0.001;
    auto topMargin = getHeight() * 0.001;
    auto dialSize = getWidth() * 0.25;
    auto buttonWidth = dialSize * 0.33;
    auto buttonHeight = buttonWidth * 0.5;
    int knobWidth = getWidth() / 2;
    int toggleWidth = knobWidth / 2;
    powerBtn.setBounds(getX() + getWidth() / 2 - toggleWidth / 2, getBottom() - 80, toggleWidth, toggleWidth);
    border.setBounds(getX() - 2, getY() - 8, getWidth() + 4, getHeight() + 10);
    indicatorLight.setBounds(getWidth() / 2 - 8, getY() + 60, 20, 20);
}

juce::Slider& PedalComponent::createKnob(juce::Component& component, juce::Slider& slider, juce::Label& label, const juce::String& id, const juce::String& name, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, double min, double max, double increment)
{
    component.addAndMakeVisible(slider);

    applyStyle(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.mTreeState, id, slider);
    slider.setRange(min, max, increment);
    slider.setName(name);
    slider.setPopupDisplayEnabled(true, true, this, 2000);
    return slider;
}

void PedalComponent::applyStyle(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    // Remove border around label
    slider.setColour(0x1001200, juce::Colour::fromFloatRGBA(0, 0, 0, 0.85f));
    slider.setColour(0x1001300, juce::Colour::fromFloatRGBA(255, 255, 255, 0.75));
    slider.setColour(0x1001310, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.65));
    slider.setColour(0x1001311, juce::Colour::fromFloatRGBA(0, 0, 0, 0.5));
    slider.setColour(0x1001400, juce::Colour::fromFloatRGBA(255, 255, 255, 0));
    slider.setColour(0x1001700, juce::Colour::fromFloatRGBA(255, 255, 255, 0.0f));
    slider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    slider.setDoubleClickReturnValue(true, 0.0);
    //slider.setTextValueSuffix(" dB");
    lameKnob.color = juce::Colours::darkgrey;
    slider.setLookAndFeel(&lameKnob);
    slider.setComponentEffect(&dialShadow);
}

void PedalComponent::applyLabelStyle(juce::String text, juce::Label& label) {
    juce::Component::addAndMakeVisible(label);
    label.setText(text, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);

    // Set label colors directly
    label.setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    label.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25));
    label.setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
}
