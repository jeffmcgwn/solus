/*
  ==============================================================================

    GateModule.cpp
    Created: 15 Jan 2024 8:49:28pm
    Author:  Jeff

  ==============================================================================
*/

#include "GateModule.h"

namespace lame_dsp
{
    NoiseGateEffect::NoiseGateEffect() : threshold(-30.0f), attackTime(10.0f), releaseTime(50.0f), holdTime(20.0f), envelope(0.0f)
    {
        // Initialize other members if needed...
    }

    float NoiseGateEffect::processSample(float inputSample)
    {
        // Calculate the envelope using simple peak detection
        float envelopeAttack = std::exp(-1.0f / (attackTime * 0.001f));
        float envelopeRelease = std::exp(-1.0f / (releaseTime * 0.001f));

        envelope = std::max(envelope * envelopeRelease, std::abs(inputSample));

        // Apply the noise gate effect
        if (envelope > threshold)
        {
            // Allow the signal through during the hold time
            envelope = std::max(envelope, threshold);
        }
        else
        {
            // Apply attack time if the signal falls below the threshold
            envelope *= envelopeAttack;
        }

        return inputSample * (envelope > threshold ? 1.0f : 0.0f);
    }

    void NoiseGateEffect::setThreshold(float newThreshold)
    {
        threshold = juce::jlimit(-80.0f, 0.0f, newThreshold);
    }

    void NoiseGateEffect::setAttackTime(float newAttackTime)
    {
        attackTime = juce::jmax(1.0f, newAttackTime);
    }

    void NoiseGateEffect::setReleaseTime(float newReleaseTime)
    {
        releaseTime = juce::jmax(1.0f, newReleaseTime);
    }

    void NoiseGateEffect::setHoldTime(float newHoldTime)
    {
        holdTime = juce::jmax(1.0f, newHoldTime);
    }

}
