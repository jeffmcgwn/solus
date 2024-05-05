/*
  ==============================================================================

    GateModule.h
    Created: 15 Jan 2024 8:49:37pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace lame_dsp
{
    class NoiseGateEffect
    {
    public:
        NoiseGateEffect();
        float processSample(float inputSample);

        // Setter methods for threshold, attack time, release time, and hold time
        void setThreshold(float newThreshold);
        void setAttackTime(float newAttackTime);
        void setReleaseTime(float newReleaseTime);
        void setHoldTime(float newHoldTime);

    private:
        float threshold;
        float attackTime;
        float releaseTime;
        float holdTime;

        float envelope; // Internal variable to track envelope
    };
}

