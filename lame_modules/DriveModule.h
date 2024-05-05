/*
  ==============================================================================

    DriveModule.h
    Created: 15 Jan 2024 8:47:05pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
namespace lame_dsp
{

    class OverdriveEffect
    {
    public:
        OverdriveEffect();
        float processSample(float inputSample);

        // Setter methods for gain, output level, and tone
        void setGain(float newGain);
        void setOutputLevel(float newOutputLevel);
        void setTone(float newTone);

    private:
        float drive; // Adjust this parameter to control the amount of overdrive
        float gain;
        float outputLevel;
        float tone;
    };
};