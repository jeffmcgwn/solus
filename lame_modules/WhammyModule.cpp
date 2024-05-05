/*
  ==============================================================================

    WhammyModule.cpp
    Created: 15 Jan 2024 8:50:02pm
    Author:  Jeff

  ==============================================================================
*/

#include "WhammyModule.h"

namespace lame_dsp
{
    PitchShiftEffect::PitchShiftEffect() : pitchShift(1.0f), windowSize(1024), readIndex(0)
    {
        circularBuffer.setSize(1, windowSize);
        circularBuffer.clear();
    }

    float PitchShiftEffect::processSample(float inputSample)
    {
        // Write the input sample to the circular buffer
        circularBuffer.getWritePointer(0)[readIndex] = inputSample;

        // Adjust read index for circular buffer
        readIndex = (readIndex + 1) % windowSize;

        // Calculate the pitch-shifted output
        int readIndexShifted = (readIndex - static_cast<int>(pitchShift * windowSize) + windowSize) % windowSize;
        float outputSample = circularBuffer.getReadPointer(0)[readIndexShifted];

        return outputSample;
    }

    void PitchShiftEffect::setPitchShift(float newPitchShift)
    {
        // Ensure newPitchShift is within a reasonable range
        pitchShift = juce::jlimit(0.5f, 2.0f, newPitchShift);
    }

    void PitchShiftEffect::setWindowSize(int newSize)
    {
        // Ensure newSize is a power of two and within a reasonable range
        windowSize = juce::nextPowerOfTwo(juce::jlimit(128, 4096, newSize));

        // Resize circular buffer
        circularBuffer.setSize(1, windowSize);
        circularBuffer.clear();
    }

}
