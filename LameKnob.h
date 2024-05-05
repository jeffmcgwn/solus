/*
  ==============================================================================

    LameKnob.h
    Created: 12 Jan 2024 7:27:48am
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/

class LameKnob : public juce::LookAndFeel_V4 {
public:
    juce::Colour color{juce::Colours::lightblue};
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override {

        float diameter = fmin(width, height);
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

        juce::Rectangle<float> dialArea(rx, ry, diameter, diameter);
        g.setColour(juce::Colour::fromFloatRGBA(0.15, 0.15, 0.15, 1)); //center
        g.setGradientFill(juce::ColourGradient::horizontal(juce::Colour::fromFloatRGBA(0.290, 0.290, 0.290, 0.8).darker(1.0), centerY * .75, juce::Colour::fromFloatRGBA(0.290, 0.290, 0.290, 0.8).darker(.5), centerY * 2.5));
        g.fillEllipse(dialArea);
        g.setColour(juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.75f)); //tick color
        
        // Value
        g.setColour(color);
        g.setFont(radius * 0.4f);
        g.drawSingleLineText(slider.getName(), centerX, centerY + radius * 1.5,
            juce::Justification::centred);
        juce::Path dialTick;
        dialTick.addRectangle(0, -radius + 3, 3.0f, radius * 0.452211);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
        g.setColour(juce::Colour::fromFloatRGBA(0, 0, 0, .25)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 1.0f);      
    }

    //void drawBubble(juce::Graphics& g, juce::BubbleComponent& bubbleComponent, const juce::Point< float >& positionOfTip, const juce::Rectangle< float >& body)
    //{
    //    bubbleComponent.setColour(0x1000af0 ,juce::Colours::black);
    //}
};
