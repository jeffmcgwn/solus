#pragma once
#include <JuceHeader.h>

/** ======= Audio Parameters ======= */

extern const juce::String gainID;
extern const juce::String gainName;

extern const juce::String outputID;
extern const juce::String outputName;

extern const juce::String hqID;
extern const juce::String hqName;

extern const juce::String speakerToggleID;
extern const juce::String speakerToggleName;

extern const juce::String channelToggleID;
extern const juce::String channelToggleName;

extern const juce::String reverbID;
extern const juce::String reverbName;

extern const juce::String reverbRoomSizeID;
extern const juce::String reverbRoomSizeName;

extern const juce::String reverbWetLevelID;
extern const juce::String reverbWetLevelName;

extern const juce::String reverbDryLevelID;
extern const juce::String reverbDryLevelName;

extern const juce::String reverbDampingID;
extern const juce::String reverbDampingName;

extern const juce::String reverbWidthID;
extern const juce::String reverbWidthName;

extern const juce::String reverbFreezeModeID;
extern const juce::String reverbFreezeModeName;

extern const juce::String reverbToggleID;
extern const juce::String reverbToggleName;

// OD
extern const juce::String overdriveID;
extern const juce::String overdriveName;


// Tube Input Gain Parameter
extern const juce::String tubeInputGainID;
extern const juce::String tubeInputGainName;

// Tube Output Gain Parameter
extern const juce::String tubeOutputGainID;
extern const juce::String tubeOutputGainName;

// Tube Drive Parameter
extern const juce::String tubeDriveID;
extern const juce::String tubeDriveName;

// Tube Bias Parameter
extern const juce::String tubeBiasID;
extern const juce::String tubeBiasName;

// Tube Mix Parameter
extern const juce::String tubeMixID;
extern const juce::String tubeMixName;

extern const juce::String lowFilterID;
extern const juce::String lowFilterName;

extern const juce::String midFilterID;
extern const juce::String midFilterName;

extern const juce::String highFilterID;
extern const juce::String highFilterName;

extern const juce::String lowCleanFilterID;
extern const juce::String lowCleanFilterName;

extern const juce::String midCleanFilterID;
extern const juce::String midCleanFilterName;

extern const juce::String highCleanFilterID;
extern const juce::String highCleanFilterName;

extern const juce::String delayMixID;
extern const juce::String delayMixName;

extern const juce::String delayFeedbackID;
extern const juce::String delayFeedbackName;

extern const juce::String delayRateID;
extern const juce::String delayRateName;

extern const juce::String delaySpreadID;
extern const juce::String delaySpreadName;

extern const juce::String delayToggleID;
extern const juce::String delayToggleName;

extern const juce::String delaySyncRateID;
extern const juce::String delaySyncRateName;

extern const juce::String delaySyncToggleID;
extern const juce::String delaySyncToggleName;
/** Sets the threshold in dB of the noise-gate.*/
extern const juce::String gateThresholdID;
extern const juce::String gateThresholdName;
/** Sets the ratio of the noise-gate (must be higher or equal to 1).*/
extern const juce::String gateRatioID;
extern const juce::String gateRatioName;
/** Sets the attack time in milliseconds of the noise-gate.*/
extern const juce::String gateAttackID;
extern const juce::String gateAttackName;
/** Sets the release time in milliseconds of the noise-gate.*/
extern const juce::String gateReleaseID;
extern const juce::String gateReleaseName;

extern const juce::String gateToggleID;
extern const juce::String gateToggleName;

// Make the same gate parameters for the clean gate
extern const juce::String cleanGateThresholdID;
extern const juce::String cleanGateThresholdName;

extern const juce::String cleanGateRatioID;
extern const juce::String cleanGateRatioName;

extern const juce::String cleanGateAttackID;
extern const juce::String cleanGateAttackName;

extern const juce::String cleanGateReleaseID;
extern const juce::String cleanGateReleaseName;

extern const juce::String cleanGateToggleID;
extern const juce::String cleanGateToggleName;

