/*
  ==============================================================================

    WhammyModule.h
    Created: 15 Jan 2024 8:50:10pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace lame_dsp
{
    class PitchShiftEffect
    {
    public:
        PitchShiftEffect();
        float processSample(float inputSample);

        // Setter methods for pitch shift amount and window size
        void setPitchShift(float newPitchShift);
        void setWindowSize(int newSize);

    private:
        float pitchShift;
        int windowSize;
        int readIndex;  // Read index for circular buffer
        juce::AudioBuffer<float> circularBuffer;
    };
}