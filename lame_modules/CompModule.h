/*
  ==============================================================================

    CompModule.h
    Created: 15 Jan 2024 8:49:54pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace lame_dsp
{
    class CompressorEffect
    {
    public:
        CompressorEffect();
        float processSample(float inputSample);

        // Setter methods for threshold, ratio, attack time, release time, and makeup gain
        void setThreshold(float newThreshold);
        void setRatio(float newRatio);
        void setAttackTime(float newAttackTime);
        void setReleaseTime(float newReleaseTime);
        void setMakeupGain(float newMakeupGain);

    private:
        float threshold;
        float ratio;
        float attackTime;
        float releaseTime;
        float makeupGain;

        float envelope; // Internal variable to track envelope
    };
}

