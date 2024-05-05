#include "Globals.h"

/** ======= Audio Parameters ======= */

const juce::String gainID = "gain";
const juce::String gainName = "Gain";

const juce::String outputID = "output";
const juce::String outputName = "Output";

const juce::String hqID = "hq";
const juce::String hqName = "High Quality";

const juce::String speakerToggleID = "speaker toggle";
const juce::String speakerToggleName = "Speaker Toggle";

const juce::String channelToggleID = "channel toggle";
const juce::String channelToggleName = "Channel Toggle";

const juce::String reverbID = "reverb";
const juce::String reverbName = "Reverb";

const juce::String reverbRoomSizeID = "reverbRoomSize";
const juce::String reverbRoomSizeName = "Reverb Room Size";

const juce::String reverbWetLevelID = "reverbWetLevel";
const juce::String reverbWetLevelName = "Reverb Wet Level";

const juce::String reverbDryLevelID = "reverbDryLevel";
const juce::String reverbDryLevelName = "Reverb Dry Level";

const juce::String reverbDampingID = "reverbDamping";
const juce::String reverbDampingName = "Reverb Damping";

const juce::String reverbWidthID = "reverbWidth";
const juce::String reverbWidthName = "Reverb Width";

const juce::String reverbFreezeModeID = "reverbFreezeMode";
const juce::String reverbFreezeModeName = "Reverb Freeze Mode";

const juce::String reverbToggleID = "reverbToggle";
const juce::String reverbToggleName = "Reverb Toggle";

// OD
const juce::String overdriveID = "overdrive";
const juce::String overdriveName = "Overdrive";


// Tube Input Gain Parameter
const juce::String tubeInputGainID = "tubeInputGain";
const juce::String tubeInputGainName = "Clean Input Gain";

// Tube Output Gain Parameter
const juce::String tubeOutputGainID = "tubeOutputGain";
const juce::String tubeOutputGainName = "Clean Output Gain";

// Tube Drive Parameter
const juce::String tubeDriveID = "tubeDrive";
const juce::String tubeDriveName = "Clean Drive";

// Tube Bias Parameter
const juce::String tubeBiasID = "tubeBias";
const juce::String tubeBiasName = "Tube Bias";

// Tube Mix Parameter
const juce::String tubeMixID = "tubeMix";
const juce::String tubeMixName = "Tube Mix";

const juce::String lowFilterID = "lowFilter";
const juce::String lowFilterName = "Low";

const juce::String midFilterID = "midFilter";
const juce::String midFilterName = "Mid";

const juce::String highFilterID = "highFilter";
const juce::String highFilterName = "High";

const juce::String lowCleanFilterID = "lowCleanFilter";
const juce::String lowCleanFilterName = "Clean Low";

const juce::String midCleanFilterID = "midCleanFilter";
const juce::String midCleanFilterName = "Clean Mid";

const juce::String highCleanFilterID = "highCleanFilter";
const juce::String highCleanFilterName = "Clean High";

const juce::String delayMixID = "delayMix";
const juce::String delayMixName = "Delay Mix";

const juce::String delayFeedbackID = "delayFeedback";
const juce::String delayFeedbackName = "Feedback";

const juce::String delayRateID = "delayRate";
const juce::String delayRateName = "Rate";

const juce::String delaySyncRateID = "delaySyncRate";
const juce::String delaySyncRateName = "Tempo Sync Rate";

const juce::String delaySyncToggleID = "delaySyncToggle";
const juce::String delaySyncToggleName = "Tempo Sync Toggle";

extern const juce::String delaySpreadID = "delaySpreadID";
extern const juce::String delaySpreadName = "Spread";

extern const juce::String delayToggleID = "delayToggleID";
extern const juce::String delayToggleName = "Delay Toggle";

extern const juce::String irID = "irID";
extern const juce::String irName = "Loaded IR";
/** Sets the threshold in dB of the noise-gate.*/
const juce::String gateThresholdID = "gateThresholdID";
const juce::String gateThresholdName = "Threshold";
/** Sets the ratio of the noise-gate (must be higher or equal to 1).*/
const juce::String gateRatioID = "gateRatioID";
const juce::String gateRatioName = "Ratio";
/** Sets the attack time in milliseconds of the noise-gate.*/
const juce::String gateAttackID = "gateAttackID";
const juce::String gateAttackName = "Attack";
/** Sets the release time in milliseconds of the noise-gate.*/
const juce::String gateReleaseID = "gateReleaseID";
const juce::String gateReleaseName = "Release";

const juce::String gateToggleID = "gateToggleID";
const juce::String gateToggleName = "Toggle";

// Make the same gate parameters for the clean gate
const juce::String cleanGateThresholdID = "cleanGateThresholdID";
const juce::String cleanGateThresholdName = "Threshold";
/** Sets the ratio of the noise-gate (must be higher or equal to 1).*/
const juce::String cleanGateRatioID = "cleanGateRatioID";
const juce::String cleanGateRatioName = "Ratio";
/** Sets the attack time in milliseconds of the noise-gate.*/
const juce::String cleanGateAttackID = "cleanGateAttackID";
const juce::String cleanGateAttackName = "Attack";
/** Sets the release time in milliseconds of the noise-gate.*/
const juce::String cleanGateReleaseID = "cleanGateReleaseID";
const juce::String cleanGateReleaseName = "Release";

const juce::String cleanGateToggleID = "cleanGateToggleID";
const juce::String cleanGateToggleName = "Toggle";