/*
  ==============================================================================

    DriveModule.cpp
    Created: 12 Jan 2024 4:58:10pm
    Author:  Jeff

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DriveModule.h"
namespace lame_dsp
{
    OverdriveEffect::OverdriveEffect() : drive(1.0f), gain(0.5f), outputLevel(1.0f), tone(0.0f)
    {
        // Initialize other members if needed...
    }

    float OverdriveEffect::processSample(float inputSample)
    {
        // Apply soft clipping to achieve overdrive effect
        float clippedSample = std::tanh(inputSample * drive);

        // Adjust the gain, output level, and tone
        float processedSample = clippedSample * gain * outputLevel;

        // Apply tone control
        processedSample = juce::jmap(processedSample, -1.0f, 1.0f, -tone, tone);

        return processedSample;
    }

    void OverdriveEffect::setTone(float newTone)
    {
        // Ensure newTone is within a reasonable range
        tone = juce::jlimit(-1.0f, 1.0f, newTone);
    }

    void OverdriveEffect::setGain(float newGain)
    {
        // Ensure newGain is within a reasonable range
        gain = juce::jlimit(0.1f, 10.0f, newGain);
    }

    void OverdriveEffect::setOutputLevel(float newOutputLevel)
    {
        // Ensure newOutputLevel is within a reasonable range
        outputLevel = juce::jlimit(0.1f, 10.0f, newOutputLevel);
    }
}