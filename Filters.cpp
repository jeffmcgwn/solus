/*
  ==============================================================================

    Filters.cpp
    Created: 11 Jan 2024 9:38:26pm
    Author:  Jeff

  ==============================================================================
*/

#include "PluginProcessor.h"

float LameAmpAudioProcessor::getShelfQ(float value)
{
    return pow(10.0f, abs(value) / 60.0f) - 0.8f;
}

float LameAmpAudioProcessor::getPeakQ(float value)
{

    if (value > 0.0f)
    {
        return pow(10.0f, abs(value) / 40.0f) - 0.9f;

    }

    else
    {
        return pow(10.0f, abs(value) / 20.0f) - 0.9f;
    }
}

float LameAmpAudioProcessor::getGain(float value)
{
    return pow(10.0f, value / 20);
}