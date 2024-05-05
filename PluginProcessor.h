/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Globals.h"
#include "lame_modules/DelayModule.h"
//==============================================================================
/**
*/
class LameAmpAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener, public juce::Component
{
public:
    //==============================================================================
    LameAmpAudioProcessor();
    ~LameAmpAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState mTreeState;
    juce::dsp::Convolution mSpeakerModule;
    juce::AudioBuffer<float> mDelayBuffer;
    int mWritePosition{ 0 };
    int mSampleRate;
    juce::File root, savedFile;
    juce::ValueTree variableTree;

private:
    static constexpr auto effectDelaySamples = 192000;
    juce::dsp::ProcessSpec mSpec;
    juce::dsp::Gain<float> mSpeakerCompensate;
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> filter1, filter2, filter3, filter4, filter5, filter6, filter7, filter8, filter9, filter10, lowFilter, midFilter, highFilter, lowCleanFilter, midCleanFilter, highCleanFilter;
    
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayModule{ effectDelaySamples };
    const juce::String* parameterIDs[37] = {
    &gainID, &outputID, &reverbID, &reverbToggleID, &reverbRoomSizeID, &reverbWetLevelID,
    &reverbDryLevelID, &reverbDampingID, &reverbWidthID, &reverbFreezeModeID,
    &tubeInputGainID, &tubeBiasID, &tubeDriveID, &tubeMixID, &tubeOutputGainID,
    &speakerToggleID, &lowFilterID, &midFilterID, &highFilterID,
    &lowCleanFilterID, &midCleanFilterID, &highCleanFilterID,
    &gateThresholdID, &gateRatioID, &gateAttackID, &gateReleaseID, &gateToggleID,
    &cleanGateThresholdID, &cleanGateRatioID, &cleanGateAttackID, &cleanGateReleaseID, &cleanGateToggleID,
    &delayRateID, &delayFeedbackID, &delayMixID, &delayToggleID, &delaySyncRateID
    };
    float delayMix{ 0.7f };
    juce::dsp::NoiseGate<float> noiseGate;
    juce::dsp::NoiseGate<float> cleanGate;
    float getShelfQ(float value);
    float getPeakQ(float value);
    float getGain(float gain);
    float mOverdriveDrive{ 0.5f };
    std::array<float, 2> lastDelayOutput;
    std::array<float, 2> delayValue { {} };
    viator_dsp::Distortion<float> mAmpDisModule;
    viator_dsp::Tube<float> mTubeModule;
    viator_dsp::SVFilter<float> mPreHPFilter, mPreMidFilter;
    Delay delay;
    void updateParams();
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    bool bpmSync;
    int subdivisionIndex;
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> myDelay{ 192000 };
    double mySampleRate{ 0.0 };
    double bpm{ 120.0 };
    juce::AudioPlayHead* playHead;
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LameAmpAudioProcessor)
};
