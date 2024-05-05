/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LameKnob.h"
#include <JuceHeader.h>
//==============================================================================
LameAmpAudioProcessor::LameAmpAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
    , mTreeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{

    variableTree = {
        "Variables", {},
        {
            { "Group", {{ "name", "AmpVars"}},
                {
                    { "Parameter", {{ "id", "file1" }, { "value", "/" }}},
                    { "Parameter", {{ "id", "file2" }, { "value", "/" }}},
                    { "Parameter", {{ "id", "root" }, { "value", "/" }}},
                }

            }
        }
    };
    
    for (const juce::String* id : parameterIDs) {
        mTreeState.addParameterListener(*id, this);
    }

    mTreeState.state.getOrCreateChildWithName("irName", nullptr); 
    mTreeState.state.getOrCreateChildWithName("root", nullptr);

    mTreeState.state = juce::ValueTree("savedParams");
}

LameAmpAudioProcessor::~LameAmpAudioProcessor()
{
    for (const juce::String* id : parameterIDs) {
        mTreeState.removeParameterListener(*id, this);
    }

}

juce::AudioProcessorValueTreeState::ParameterLayout LameAmpAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(outputID, outputName, -24.0f, 24.0f, -10.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(gainID, gainName, 0.0f, 40.0f, 32.0f));
    // Reverb
    params.push_back(std::make_unique<juce::AudioParameterBool>(reverbToggleID, reverbToggleName, true));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(reverbRoomSizeID, reverbRoomSizeName, 0.0f, 1.0, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(reverbWetLevelID, reverbWetLevelName, 0.0f, 1.0, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(reverbDampingID, reverbDampingName, 0.0f, 1.0, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(reverbWidthID, reverbWidthName, 0.0f, 1.0, 0.5f));

    // OD
    params.push_back(std::make_unique<juce::AudioParameterFloat>(overdriveID, overdriveName, 0.0f, 1.0f, 0.5f));

    // Tube
    // Tube Input Gain Parameter
    params.push_back(std::make_unique<juce::AudioParameterFloat>(tubeInputGainID, tubeInputGainName, -24.0f, 24.0f, -10.0f));

    // Tube Output Gain Parameter
    params.push_back(std::make_unique<juce::AudioParameterFloat>(tubeOutputGainID, tubeOutputGainName, -24.0f, 0.0f, -12.0f));

    //// Tube Drive Parameter
    params.push_back(std::make_unique<juce::AudioParameterFloat>(tubeDriveID, tubeDriveName, -24.0f, 24.0f, 0.0f));

    // Tube Mix Parameter
    //params.push_back(std::make_unique<juce::AudioParameterFloat>(tubeMixID, tubeMixName, -24.0f, 24.0f, 0.0f));

    // Speaker
    params.push_back(std::make_unique<juce::AudioParameterBool>(speakerToggleID, speakerToggleName, true));

    // EQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(lowFilterID, lowFilterName, -12.0f, 12.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(midFilterID, midFilterName, -12.0f, 12.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(highFilterID, highFilterName, -12.0f, 12.0f, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(lowCleanFilterID, lowCleanFilterName, -12.0f, 12.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(midCleanFilterID, midCleanFilterName, -12.0f, 12.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(highCleanFilterID, highCleanFilterName, -12.0f, 12.0f, 0.0f));

    // Gate
    params.push_back(std::make_unique<juce::AudioParameterBool>(gateToggleID, gateToggleName, true));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(gateThresholdID, gateThresholdName, -100.0f, 6.0f, -22.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(gateAttackID, gateAttackName, -0.0f, 250.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(gateReleaseID, gateReleaseName, -0.0f, 1500.0f, 100.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(gateRatioID, gateRatioName, 1.0f, 10.0f, 1.0f));

    // Clean Gate
    params.push_back(std::make_unique<juce::AudioParameterBool>(cleanGateToggleID, cleanGateToggleName, false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(cleanGateThresholdID, cleanGateThresholdName, -100.0f, 6.0f, -19.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(cleanGateAttackID, cleanGateAttackName, -0.0f, 250.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(cleanGateReleaseID, cleanGateReleaseName, -0.0f, 1500.0f, 100.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(cleanGateRatioID, cleanGateRatioName, 1.0f, 10.0f, 1.0f));
    //params.push_back(std::make_unique<juce::AudioParameterBool>(delayToggleID, delayToggleName, true));


    // Clean Toggle
    params.push_back(std::make_unique<juce::AudioParameterBool>(channelToggleID, channelToggleName, false));

    delay.setParams(params);

    return { params.begin(), params.end() };
}

void LameAmpAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    //delayModule.setDelay(newValue / 1000.0f * getSampleRate());

    updateParams();
}

void LameAmpAudioProcessor::updateParams()
{
    // Dist
    mAmpDisModule.setOutput(mTreeState.getRawParameterValue(outputID)->load());
    mAmpDisModule.setDrive(mTreeState.getRawParameterValue(gainID)->load());

    //Gate
    noiseGate.setAttack(mTreeState.getRawParameterValue(gateAttackID)->load());
    noiseGate.setRatio(mTreeState.getRawParameterValue(gateRatioID)->load());
    noiseGate.setThreshold(mTreeState.getRawParameterValue(gateThresholdID)->load());
    noiseGate.setRelease(mTreeState.getRawParameterValue(gateReleaseID)->load());

    cleanGate.setAttack(mTreeState.getRawParameterValue(cleanGateAttackID)->load());
    cleanGate.setRatio(mTreeState.getRawParameterValue(cleanGateRatioID)->load());
    cleanGate.setThreshold(mTreeState.getRawParameterValue(cleanGateThresholdID)->load());
    cleanGate.setRelease(mTreeState.getRawParameterValue(cleanGateReleaseID)->load());


    // Reverb
    reverbParams.wetLevel = mTreeState.getRawParameterValue(reverbWetLevelID)->load();
    reverbParams.roomSize = mTreeState.getRawParameterValue(reverbRoomSizeID)->load();
    reverbParams.damping = mTreeState.getRawParameterValue(reverbDampingID)->load();
    reverbParams.width = mTreeState.getRawParameterValue(reverbWidthID)->load();
    reverb.setParameters(reverbParams);

    // OD
    mOverdriveDrive = mTreeState.getRawParameterValue(overdriveID)->load();

    // Tube
    mTubeModule.setMix(10);
    mTubeModule.setInputGain(mTreeState.getRawParameterValue(tubeInputGainID)->load());
    mTubeModule.setOutputGain(mTreeState.getRawParameterValue(tubeOutputGainID)->load());
    mTubeModule.setDrive(mTreeState.getRawParameterValue(tubeDriveID)->load());

    // Adjust the following line based on your actual tube module parameter
    //mTubeModule.setMix(mTreeState.getRawParameterValue(tubeMixID)->load());

    // EQ
    if (mSpec.sampleRate > 0)
    {
        *lowFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(mSpec.sampleRate, 125.0f, getShelfQ(mTreeState.getRawParameterValue(lowFilterID)->load()), getGain(mTreeState.getRawParameterValue(lowFilterID)->load()));
        *midFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 800.0f, getShelfQ(mTreeState.getRawParameterValue(midFilterID)->load()), getGain(mTreeState.getRawParameterValue(midFilterID)->load()));
        *highFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(mSpec.sampleRate, 2000.0f, getShelfQ(mTreeState.getRawParameterValue(highFilterID)->load()), getGain(mTreeState.getRawParameterValue(highFilterID)->load()));

        *lowCleanFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(mSpec.sampleRate, 125.0f, getShelfQ(mTreeState.getRawParameterValue(lowCleanFilterID)->load()), getGain(mTreeState.getRawParameterValue(lowCleanFilterID)->load()));
        *midCleanFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 800.0f, getShelfQ(mTreeState.getRawParameterValue(midCleanFilterID)->load()), getGain(mTreeState.getRawParameterValue(midCleanFilterID)->load()));
        *highCleanFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(mSpec.sampleRate, 2000.0f, getShelfQ(mTreeState.getRawParameterValue(highCleanFilterID)->load()), getGain(mTreeState.getRawParameterValue(highCleanFilterID)->load()));
    }



    // Delay
    delay.updateParams(mTreeState, getSampleRate(), mTreeState.getRawParameterValue(delaySyncToggleID)->load(), bpm);
}

//==============================================================================


const juce::String LameAmpAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LameAmpAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LameAmpAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LameAmpAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LameAmpAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LameAmpAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LameAmpAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LameAmpAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LameAmpAudioProcessor::getProgramName (int index)
{
    return {};
}

void LameAmpAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


//==============================================================================
void LameAmpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int numInputChannels = getNumInputChannels();


    mSpec.maximumBlockSize = samplesPerBlock;
    mSpec.sampleRate = sampleRate;
    mSpec.numChannels = getTotalNumOutputChannels();

    delay.prepare(mTreeState, sampleRate, mSpec);

    noiseGate.prepare(mSpec);
    cleanGate.prepare(mSpec);
    mSpeakerModule.prepare(mSpec);
    if (savedFile.existsAsFile()) {
        mSpeakerModule.loadImpulseResponse(savedFile, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
    }
    else {
        savedFile = BinaryData::GuitarHack_Centre_45_wav;
        mSpeakerModule.loadImpulseResponse(BinaryData::GuitarHack_Centre_45_wav, BinaryData::GuitarHack_Centre_45_wavSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
    }

    mSpeakerCompensate.prepare(mSpec);
    mSpeakerCompensate.setRampDurationSeconds(0.02);
    mSpeakerCompensate.setGainDecibels(14.0);

    mTubeModule.prepare(mSpec);
    mTubeModule.setBias(0);

    mAmpDisModule.prepare(mSpec);
    mAmpDisModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kTube);
    mPreHPFilter.prepare(mSpec);
    mPreHPFilter.setStereoType(viator_dsp::SVFilter<float>::StereoId::kStereo);
    mPreHPFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighPass);
    mPreHPFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQType, viator_dsp::SVFilter<float>::QType::kParametric);
    mPreHPFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, 100);
    filter1.prepare(mSpec);
    filter2.prepare(mSpec);
    filter3.prepare(mSpec);
    filter4.prepare(mSpec);
    filter5.prepare(mSpec);
    filter6.prepare(mSpec);
    filter7.prepare(mSpec);
    filter8.prepare(mSpec);
    filter9.prepare(mSpec);
    filter10.prepare(mSpec);
    lowFilter.prepare(mSpec);
    midFilter.prepare(mSpec);
    highFilter.prepare(mSpec);

    lowCleanFilter.prepare(mSpec);
    midCleanFilter.prepare(mSpec);
    highCleanFilter.prepare(mSpec);

    *filter1.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(mSpec.sampleRate, 50.0f, getShelfQ(-12), getGain(-12));
    *filter2.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 63.0f, getPeakQ(-6.5), getGain(-6.5));
    *filter3.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 125.0f, getPeakQ(-6.75), getGain(-6.75));
    *filter4.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 250.0f, getPeakQ(0), getGain(0));
    *filter5.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 500.0f, getPeakQ(1), getGain(1));
    *filter6.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 1000.0f, getPeakQ(2), getGain(2));
    *filter7.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 2000.0f, getPeakQ(0.75), getGain(0.75));
    *filter8.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 4000.0f, getPeakQ(-0.25), getGain(-0.25));
    *filter9.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(mSpec.sampleRate, 8000.0f, getPeakQ(1.25), getGain(1.25));
    *filter10.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(mSpec.sampleRate, 9000.0f, getShelfQ(-11.5), getGain(-11.5));
    reverbParams.dryLevel = 0.5;
    reverb.setParameters(reverbParams);
    reverb.prepare(mSpec);

    updateParams();
}

void LameAmpAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LameAmpAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void LameAmpAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    const auto numChannels = juce::jmax(totalNumInputChannels, totalNumOutputChannels);

    juce::dsp::AudioBlock<float> block{ buffer };

    mOverdriveDrive = mTreeState.getRawParameterValue(overdriveID)->load();

    if (mTreeState.getRawParameterValue(channelToggleID)->load())
    {
        mTubeModule.process(juce::dsp::ProcessContextReplacing<float>(block));
        lowCleanFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        midCleanFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        highCleanFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        if (mTreeState.getRawParameterValue(cleanGateToggleID)->load())
        {
            cleanGate.process(juce::dsp::ProcessContextReplacing<float>(block));
        }
    }
    else {
        mPreHPFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        mAmpDisModule.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter1.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter2.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter3.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter4.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter5.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter6.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter7.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter8.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter9.process(juce::dsp::ProcessContextReplacing<float>(block));
        filter10.process(juce::dsp::ProcessContextReplacing<float>(block));
        lowFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        midFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        highFilter.process(juce::dsp::ProcessContextReplacing<float>(block));

        const float currentGain = mTreeState.getRawParameterValue(gainID)->load();
        
        buffer.applyGain(currentGain * 0.1f);

        if (mTreeState.getRawParameterValue(gateToggleID)->load())
        {
            noiseGate.process(juce::dsp::ProcessContextReplacing<float>(block));
        }
    }



    if (mTreeState.getRawParameterValue(reverbToggleID)->load())
    {
        reverb.process(juce::dsp::ProcessContextReplacing<float>(block));
    }

    if (mTreeState.getRawParameterValue(delayToggleID)->load())
    {
        delay.process(buffer, mTreeState, numChannels);
    }

    if (mTreeState.getRawParameterValue(speakerToggleID)->load())
    {
        mSpeakerModule.process(juce::dsp::ProcessContextReplacing<float>(block));
        mSpeakerCompensate.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    auto tmp_bpm = this->getPlayHead()->getPosition()->getBpm();

    // NOTE: When you're running standalone, you won't get a value here, as there is no host environment
    if (mTreeState.getRawParameterValue(delaySyncToggleID) -> load()) {
        // Set your module level variable to the retrieved value, for use elsewhere
        if (tmp_bpm.hasValue() && tmp_bpm != bpm) {
            bpm = (int)*tmp_bpm;
        }
        delay.setDelayTime(mTreeState, getSampleRate(), true, bpm);
    }
}

//==============================================================================
bool LameAmpAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LameAmpAudioProcessor::createEditor()
{
     return new LameAmpAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void LameAmpAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto thing = variableTree.getProperty("file1");

    juce::MemoryOutputStream stream(destData, false);
    mTreeState.state.writeToStream(stream);
}

void LameAmpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    if (tree.isValid())
    {
        mTreeState.state = tree;
        savedFile = juce::File(mTreeState.state.getProperty("irName"));
        root = juce::File(mTreeState.state.getProperty("root"));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LameAmpAudioProcessor();
}
