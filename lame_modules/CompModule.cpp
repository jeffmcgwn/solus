/*
  ==============================================================================

    CompModule.cpp
    Created: 15 Jan 2024 8:49:46pm
    Author:  Jeff

  ==============================================================================
*/

#include "CompModule.h"

namespace lame_dsp
{
    CompressorEffect::CompressorEffect() : threshold(-20.0f), ratio(4.0f), attackTime(10.0f), releaseTime(50.0f), makeupGain(0.0f), envelope(0.0f)
    {
        // Initialize other members if needed...
    }

    float CompressorEffect::processSample(float inputSample)
    {
        // Calculate the envelope using simple RMS detection
        float envelopeAttack = std::exp(-1.0f / (attackTime * 0.001f));
        float envelopeRelease = std::exp(-1.0f / (releaseTime * 0.001f));

        envelope = envelope * envelopeRelease + std::pow(inputSample, 2.0f);

        // Apply the compressor effect
        float gainReduction = 0.0f;
        if (envelope > threshold)
        {
            gainReduction = (envelope - threshold) / (1.0f + ratio);
        }

        // Apply makeup gain to compensate for gain reduction
        float outputSample = inputSample * juce::Decibels::decibelsToGain(-gainReduction + makeupGain);

        return outputSample;
    }

    void CompressorEffect::setThreshold(float newThreshold)
    {
        threshold = newThreshold;
    }

    void CompressorEffect::setRatio(float newRatio)
    {
        ratio = juce::jmax(1.0f, newRatio);
    }

    void CompressorEffect::setAttackTime(float newAttackTime)
    {
        attackTime = juce::jmax(1.0f, newAttackTime);
    }

    void CompressorEffect::setReleaseTime(float newReleaseTime)
    {
        releaseTime = juce::jmax(1.0f, newReleaseTime);
    }

    void CompressorEffect::setMakeupGain(float newMakeupGain)
    {
        makeupGain = newMakeupGain;
    }

}
