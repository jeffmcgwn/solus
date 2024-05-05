/*
  ==============================================================================

    DelayModule.h
    Created: 29 Jan 2024 9:14:06am
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Globals.h"

class Delay
{
public:
    void setParams(std::vector <std::unique_ptr<juce::RangedAudioParameter>>& params) {
        params.push_back(std::make_unique<juce::AudioParameterFloat>(delayRateID, delayRateName, 0.01f, 1000.0f, 500.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(delayFeedbackID, delayFeedbackName, 0.0f, 1.0f, 0.25f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(delayMixID, delayMixName, 0.0f, 1.5f, 0.7f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(delaySpreadID, delaySpreadName, 0.0f, 50.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(delaySyncRateID, delaySyncRateName, 0, 11, 6));
        params.push_back(std::make_unique<juce::AudioParameterBool>(delayToggleID, delayToggleName, true));
        params.push_back(std::make_unique<juce::AudioParameterBool>(delaySyncToggleID, delaySyncToggleName, true));

    }
    void updateParams(juce::AudioProcessorValueTreeState& apvts, double sampleRate, bool bpmSync, float bpm) {
        setDelayTime(apvts, sampleRate, bpmSync, bpm);
        delayMix = apvts.getRawParameterValue(delayMixID)->load();
    }

    void setDelayTime(const juce::AudioProcessorValueTreeState& apvts, double sampleRate, bool bpmSync, float bpm)
    {
        // convert delay time to samples based on sync status
        if (bpmSync)
        {
            delayModule.setDelay(subdivisions[apvts.getRawParameterValue(delaySyncRateID)->load()] * sampleRate * 60.0 / bpm);
        }
        else
        {
            delayModule.setDelay(apvts.getRawParameterValue(delayRateID)->load() / 1000.0 * sampleRate);
        }
    }

    void prepare(juce::AudioProcessorValueTreeState& apvts, double sampleRate, juce::dsp::ProcessSpec spec, bool bpmSync = false, float bpm = 120) {
        delayModule.prepare(spec);
        delayModule.reset();
        std::fill(lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f);
        setDelayTime(apvts, sampleRate, bpmSync, bpm);
    }
    
    void process(juce::AudioBuffer<float>& buffer, juce::AudioProcessorValueTreeState& apvts, int numChannels) {
        auto audioBlock = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, (size_t)numChannels);
        auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
        const auto& input = context.getInputBlock();
        const auto& output = context.getOutputBlock();
        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* samplesIn = input.getChannelPointer(channel);
            auto* samplesOut = output.getChannelPointer(channel);

            for (size_t sample = 0; sample < input.getNumSamples(); ++sample)
            {
                auto input = samplesIn[sample] - lastDelayOutput[channel];
                auto delayAmount = delayValue[channel];
                delayModule.pushSample((int)channel, input);

                samplesOut[sample] += delayModule.popSample((int)channel) * delayMix;

                // Feedback
                lastDelayOutput[channel] = samplesOut[sample] * apvts.getRawParameterValue(delayFeedbackID)->load();
            }
        }
    }
    struct Parameters {
        float delayTime, feedback, width, mix,
            modRate, modDepth, hpfFreq, lpfFreq, drive;
        bool bpmSync;
        int subdivisionIndex;
    };
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayModule{ 192000 };
    bool bpmSync;
    double sampleRate{ 0.0 };
    int bufferSize{ 0 };
    int delayBufferSize{ 0 };
    int writePosition{ 0 };
    double bpm{ 120.0 };
    int subdivisionIndex;
    std::array<float, 2> lastDelayOutput;
    std::array<float, 2> delayValue{ {} };
    float delayMix{ 0.7f };
    const std::array<float, 12> subdivisions{ 0.25f, (0.5f / 3.0f), 0.375f, 0.5f,
        (1.0f / 3.0f), 0.75f, 1.0f, (2.0f / 3.0f), 1.5f, 2.0f, (4.0f / 3.0f), 3.0f };

    juce::StringArray delaySubdivisions{ "16th", "16th Triplet", "16th Dotted",
        "8th", "8th Triplet", "8th Dotted", "Quarter", "Quarter Triplet", "Quarter Dotted",
        "Half", "Half Triplet", "Half Dotted" };

    Parameters parameters;
private:
};